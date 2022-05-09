/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/08 17:10:20 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int	cd_empty(t_vars *vars);
static int	cd_other(char *pathname, t_vars *vars);
static char	*manage_tild(char *pathname, t_vars *vars);
static bool	is_good_path(char *pathname, t_vars *vars);

/* ************************************************************************** */
int cd_builtin(t_vars *vars, char **cmd_args)
{
	if (cmd_args[1] == NULL || cmd_args[1][0] == '\0')
		return (cd_empty(vars));		

	cmd_args[1] = manage_tild(cmd_args[1], vars);
	
	return (cd_other(cmd_args[1], vars));
}

/* ************************************************************************** */
static int cd_empty(t_vars *vars)
{
	char	*path;

	path = get_var(vars->env, "HOME")->data; 
	return (cd_other(path, vars));
}

/* ************************************************************************** */
static int cd_other(char *pathname, t_vars *vars)
{
	char cwd[CWD_BUF_SIZE];
	char oldcwd[CWD_BUF_SIZE];
	
	if(getcwd(oldcwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", errno));
	
	if (chdir(pathname) == CHDIR_ERROR)
	{
		ft_printf("minishell: cd: ");
		return (manage_perror(pathname, errno));
	}
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", errno));
	
	update_var(&vars->env, "OLDPWD", oldcwd);
	update_var(&vars->env, "PWD", cwd);

	return (BUILTIN_SUCCESS);	
}

/* ************************************************************************** */
// static void print_cmd_args(char **cmd_args)
// {
// 	int i;
	
// 	ft_printf("\n");
// 	i = 0;
// 	while (cmd_args[i] != NULL)
// 	{
// 		ft_printf("cmd_args[%d]: %s\n", i, cmd_args[i]);
// 		i++;
// 	}	
// 	ft_printf("\n");	
// }

/* ************************************************************************** */
static char *manage_tild(char *pathname, t_vars *vars)
{
	int len;
	char *buff1;
	char *buff2;
	
	buff1 = NULL;
	buff2 = NULL;

	len = 0;	
	if (pathname[0] == '~')
	{
		buff1 = get_var(vars->env, "HOME")->data;
		len = ft_strlen(pathname);
		buff2 = ft_substr(pathname, 1, len - 1);
		ft_free_null((void**)&pathname);
		pathname = ft_strjoin(buff1, buff2);
		ft_free_null((void**)&buff2);		
	}
	return (pathname);	
}

/* ************************************************************************** */
// ATTENTION: il faut donner un PATH ABSOLUE
/* ************************************************************************** */
static bool is_good_path(char *pathname, t_vars *vars)
{
	DIR	*folder;
	
	(void)vars;
	folder = opendir(pathname);
	if (folder == NULL)
		return (false);	
	closedir(folder);	
	return (true);	
}

/* ************************************************************************** */