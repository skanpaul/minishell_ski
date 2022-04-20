/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/04/20 20:19:45 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
#define CD_NO_ERROR		0
#define CD_ERROR		-1
#define CD_MSG_ERR_NO_ARG		"cd: need a relative or absolut path"
/* ************************************************************************** */
#define CHDIR_NO_ERROR	0
#define CHDIR_ERROR		-1
/* ************************************************************************** */
#define MSG_ERR_GETCWD			"getcwd() "
/* ************************************************************************** */
static int manage_error(char *remark);
static int cd_empty(void);
static int cd_point(char *pathname, t_maillon **ptr_env);
static int cd_other();
/* ************************************************************************** */
int cd_builtin(char *pathname, t_maillon **ptr_env)
{
	if (pathname == NULL || pathname[0] == '\0')
		return (cd_empty());

	else if (ft_strncmp(pathname, ".", 2)  == 0)
		return (cd_point(pathname, ptr_env));

	else
		return (cd_other(pathname, ptr_env));

	return (CD_NO_ERROR);
}

/* ************************************************************************** */
static int manage_error(char *remark)
{
	perror(remark);
	printf("\n");
	return (CD_ERROR);
}

/* ************************************************************************** */
static int cd_empty(void)
{
	write(1, CD_MSG_ERR_NO_ARG, ft_strlen(CD_MSG_ERR_NO_ARG));
	write(1, "\n", 1);
	write(1, "\n", 1);
	return (CD_ERROR);
}
/* ************************************************************************** */
static int cd_point(char *pathname, t_maillon **ptr_env)
{
	char cwd[4096];
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_error(pathname));
		
	if(getcwd(cwd, 4096) == NULL)
		return(manage_error(MSG_ERR_GETCWD));
		
	replace_env_oldpwd(ptr_env, cwd);
	
	return (CD_NO_ERROR);	
}
/* ************************************************************************** */
static int cd_other(char *pathname, t_maillon **ptr_env)
{
	char cwd[4096];
	char oldcwd[4096];
	
	if(getcwd(oldcwd, 4096) == NULL)
		return(manage_error(MSG_ERR_GETCWD));
		
	if (chdir(pathname) == CHDIR_ERROR)
		return (manage_error(pathname));
		
	if(getcwd(cwd, 4096) == NULL)
		return(manage_error(MSG_ERR_GETCWD));
	
	replace_env_oldpwd(ptr_env, oldcwd);
	replace_env_pwd(ptr_env, cwd);

	return (CD_NO_ERROR);	
}

/* ************************************************************************** */