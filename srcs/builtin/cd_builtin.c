/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/18 17:53:35 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static int	cd_empty(t_vars *vars);
static int	cd_other(char *pathname, t_vars *vars);
static char	*manage_tild(char *pathname, t_vars *vars);
// static bool	is_good_path(char *pathname, t_vars *vars);
static int	cd_hyphen(t_vars *vars);

/* ************************************************************************** */
int	cd_builtin(t_vars *vars, char **cmd_args)
{
	if (cmd_args[1] == NULL || cmd_args[1][0] == '\0'
		|| does_word_match(cmd_args[1], "--"))
		return (cd_empty(vars));
	if (does_word_match(cmd_args[1], "-"))
		return (cd_hyphen(vars));
	if (does_wordstart_match(cmd_args[1], "-")
		|| does_wordstart_match(cmd_args[1], "--"))
	{
		ft_printf("minishell: cd: ");
		write(1, cmd_args[1], 2);
		ft_printf(": invalid option\n");
		return (BUILTIN_FAILURE);
	}
	cmd_args[1] = manage_tild(cmd_args[1], vars);
	return (cd_other(cmd_args[1], vars));
}

/* ************************************************************************** */
static int	cd_empty(t_vars *vars)
{
	char	*path;

	if (!does_var_exist(vars->env, "HOME"))
	{
		ft_printf("minishell: cd: PWD not set\n");
		return (BUILTIN_FAILURE_PLUS);
	}
	path = get_var(vars->env, "HOME")->data;
	return (cd_other(path, vars));
}

/* ************************************************************************** */
static int	cd_hyphen(t_vars *vars)
{
	t_env	*temp_oldpwd;

	temp_oldpwd = NULL;
	if (!does_var_exist(vars->env, "OLDPWD"))
	{
		ft_printf("minishell: cd: OLDPWD not set\n");
		return (BUILTIN_FAILURE_PLUS);
	}
	temp_oldpwd = get_var(vars->env, "OLDPWD");
	ft_printf("%s\n", temp_oldpwd->data);
	return (cd_other(temp_oldpwd->data, vars));
}

/* ************************************************************************** */
static int	cd_other(char *pathname, t_vars *vars)
{
	char	cwd[CWD_BUF_SIZE];
	char	oldcwd[CWD_BUF_SIZE];

	if (getcwd(oldcwd, CWD_BUF_SIZE) == NULL) // free ?
		return (manage_perror("cd_builtin: [ getcwd() ] ", errno));
	if (chdir(pathname) == CHDIR_ERROR)
	{
		ft_printf("minishell: cd: ");
		return (manage_perror(pathname, errno));
	}		
	if (getcwd(cwd, CWD_BUF_SIZE) == NULL)  // free ?
		return (manage_perror("cd_builtin: [ getcwd() ] ", errno));
	update_var(&vars->env, "OLDPWD", oldcwd);
	update_var(&vars->env, "PWD", cwd);
	return (BUILTIN_SUCCESS);
}

/* ************************************************************************** */
// Le symbole [ ~ ] n'est pas compris par chdir()
static char	*manage_tild(char *pathname, t_vars *vars)
{
	int		len;
	char	*buff1;
	char	*buff2;

	buff1 = NULL;
	buff2 = NULL;
	len = 0;
	if (pathname[0] == '~')
	{
		buff1 = get_var(vars->env, "HOME")->data;
		len = ft_strlen(pathname);
		buff2 = ft_substr(pathname, 1, len - 1);
		ft_free_null((void **)&pathname);
		pathname = ft_strjoin(buff1, buff2);
		ft_free_null((void **)&buff2);
	}
	return (pathname);
}

/* ************************************************************************** */
// ATTENTION: il faut donner un PATH ABSOLUE
// static bool	is_good_path(char *pathname, t_vars *vars)
// {
// 	DIR	*folder;

// 	(void)vars;
// 	folder = opendir(pathname);
// 	if (folder == NULL)
// 		return (false);
// 	closedir(folder);
// 	return (true);
// }

/* ************************************************************************** */
