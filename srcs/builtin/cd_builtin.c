/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/04/28 15:31:35 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int	cd_empty(t_vars *vars);
static int	cd_point(char *pathname, t_vars *vars);
static int	cd_other(char *pathname, t_vars *vars);
static char	*manage_tild(char *pathname, t_vars *vars);

/* ************************************************************************** */
int cd_builtin(char *pathname, t_vars *vars)
{
	if (pathname == NULL || pathname[0] == '\0')
		return (cd_empty(vars));

	pathname = manage_tild(pathname, vars);

	//*pathname == '.';
	if (ft_strncmp(pathname, ".", 2)  == 0)
		return (cd_point(pathname, vars));		
	else
		return (cd_other(pathname, vars));
	
	write_exit_success(vars);
	return (BUILTIN_SUCCESS);
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
		return(manage_perror("1 cd_builtin: [ getcwd() ] ", vars));
	
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_perror(pathname, vars));
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("2 cd_builtin: [ getcwd() ] ", vars));
	
	update_var(&vars->env, "OLDPWD", oldcwd);
	update_var(&vars->env, "PWD", cwd);

	write_exit_success(vars);
	return (BUILTIN_SUCCESS);	
}

/* ************************************************************************** */
char *manage_tild(char *pathname, t_vars *vars)
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
		free(pathname);
		pathname = ft_strjoin(buff1, buff2);	
		free(buff2);	
	}
	return (pathname);	
}

/* ************************************************************************** */
// void print_pwd_and_oldpwd(t_vars *vars)
// {
// 	ft_printf("PWD   : [ %s ]\n", get_var(vars->env, "PWD")->data);
// 	ft_printf("OLDPWD: [ %s ]\n", get_var(vars->env, "OLDPWD")->data);	
// }
// ft_printf("\nAVANT ****************************\n");
// print_pwd_and_oldpwd(vars);
// cd_builtin(cmd_args[1], vars); //add error if cmd_args[2]
// ft_printf("\nAPRES =============================\n");
// print_pwd_and_oldpwd(vars);
// ft_printf("\n");