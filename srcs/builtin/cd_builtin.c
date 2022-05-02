/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/02 14:36:25 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int	cd_empty(t_vars *vars);
static int	cd_bad_path(char *pathname, t_vars *vars);
static int	cd_point(char *pathname, t_vars *vars);
static int	cd_other(char *pathname, t_vars *vars);

/* ************************************************************************** */
int cd_builtin(t_vars *vars, char **cmd_args)
{
	if (cmd_args[1] == NULL || cmd_args[1][0] == '\0')
		return (cd_empty(vars));	
		
	if (is_good_path(cmd_args[1], vars) == false)
		return (cd_bad_path(cmd_args[1], vars));	

	cmd_args[1] = manage_tild(cmd_args[1], vars);	
	
	if (ft_strncmp(cmd_args[1], ".", 2)  == 0)
		return (cd_point(cmd_args[1], vars));
	
	return (cd_other(cmd_args[1], vars));
}

/* ************************************************************************** */
static int	cd_bad_path(char *pathname, t_vars *vars)
{
	ft_printf("minishell: cd: ");
	ft_printf("%s: No such file or directory\n", pathname);
	
	write_exit_failure(vars);
	return BUILTIN_FAILURE;	
}

/* ************************************************************************** */
static int cd_empty(t_vars *vars)
{
	char	*path;

	path = get_var(vars->env, "HOME")->data; 
	return (cd_other(path, vars));
}
/* ************************************************************************** */
static int cd_point(char *pathname, t_vars *vars)
{
	char cwd[CWD_BUF_SIZE];

	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_perror(pathname, vars));
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", vars));
		
	update_var(&vars->env, "OLDPWD", cwd);
	
	write_exit_success(vars);
	return (BUILTIN_SUCCESS);	
}
/* ************************************************************************** */
static int cd_other(char *pathname, t_vars *vars)
{
	char cwd[CWD_BUF_SIZE];
	char oldcwd[CWD_BUF_SIZE];
	
	if(getcwd(oldcwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", vars));
	
	if (chdir(pathname) == CHDIR_ERROR)
	{
		ft_printf("minishell: cd: ");
		return (manage_perror(pathname, vars));
	}
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", vars));
	
	update_var(&vars->env, "OLDPWD", oldcwd);
	update_var(&vars->env, "PWD", cwd);

	write_exit_success(vars);
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