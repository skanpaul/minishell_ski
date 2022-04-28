/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/04/28 16:32:23 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int	cd_empty(t_vars *vars);
static int	cd_point(char *pathname, t_vars *vars);
static int	cd_other(char *pathname, t_vars *vars);

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
		return(manage_perror("cd_builtin: [ getcwd() ] ", vars));
	
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_perror(pathname, vars));
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("cd_builtin: [ getcwd() ] ", vars));
	
	update_var(&vars->env, "OLDPWD", oldcwd);
	update_var(&vars->env, "PWD", cwd);

	write_exit_success(vars);
	return (BUILTIN_SUCCESS);	
}

/* ************************************************************************** */
