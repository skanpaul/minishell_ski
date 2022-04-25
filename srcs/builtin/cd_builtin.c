/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/04/25 16:43:19 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int cd_empty(t_env **ptr_env);
static int cd_point(char *pathname, t_env **ptr_env);
static int cd_other();
/* ************************************************************************** */
int cd_builtin(char *pathname, t_env **ptr_env)
{
	if (pathname == NULL || pathname[0] == '\0')
		return (cd_empty(ptr_env));

	//*pathname == '.';
	else if (ft_strncmp(pathname, ".", 2)  == 0)
		return (cd_point(pathname, ptr_env));

	else
		return (cd_other(pathname, ptr_env));

	return (CD_NO_ERROR);
}

/* ************************************************************************** */
static int cd_empty(t_env **ptr_env)
{
	char	*path;

	path = get_env(*ptr_env, "HOME")->data; 
	return (cd_other(path, ptr_env));
}
/* ************************************************************************** */
static int cd_point(char *pathname, t_env **ptr_env)
{
	char cwd[CWD_BUF_SIZE];
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_perror(pathname));
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("getcwd() "));
		
	replace_env_oldpwd(ptr_env, cwd);
	
	return (CD_NO_ERROR);	
}
/* ************************************************************************** */
static int cd_other(char *pathname, t_env **ptr_env)
{
	char cwd[CWD_BUF_SIZE];
	char oldcwd[CWD_BUF_SIZE];
	
	if(getcwd(oldcwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("getcwd() "));
		
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_perror(pathname));
		
	if(getcwd(cwd, CWD_BUF_SIZE) == NULL)
		return(manage_perror("getcwd() "));
	
	replace_env_oldpwd(ptr_env, oldcwd);
	replace_env_pwd(ptr_env, cwd);

	return (CD_NO_ERROR);	
}

/* ************************************************************************** */
