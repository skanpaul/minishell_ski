/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/15 22:08:48 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* ************************************************************************** */
static void add_minishell_to_path(t_vars *vars);

/* ************************************************************************** */
static void copy_parent_env(t_env **child_env, char **parent_env)
{
	char	*name;
	char	*data;
	int		len;

	while (*parent_env)
	{
		len = ft_strchr(*parent_env, '=') - *parent_env;
		name = ft_substr(*parent_env, 0, len);
		data = ft_substr(*parent_env, len + 1, ft_strlen(*parent_env));
		add_var(child_env, name, data);
		ft_free_null((void**)&name);
		ft_free_null((void**)&data);
		parent_env++;
	}
}

/* ************************************************************************** */
void	init_env(t_vars *vars, char **envp)
{
	char	*temp_str;

	temp_str = NULL;

	copy_parent_env(&vars->env, envp);
	remove_var(&vars->env, "OLDPWD");
	
	// Update: SHLVL
	temp_str = ft_itoa(ft_atoi(get_var(vars->env, "SHLVL")->data) + 1);
	update_var(&vars->env, "SHLVL", temp_str);
	ft_free_null((void **)&temp_str);	

	// AJOUTER le path de [./minishell] dans la variable d'environnement $PATH
	add_minishell_to_path(vars);

	//assurer que PATH, HOME, PWD, OLDPWD, SHLVL SONT PRESENTS
	//sinon -> les ajouter
	
}

/* ************************************************************************** */
int	env_builtin(t_vars *vars)
{
	print_var(vars->env);
	return (0);
}

/* ************************************************************************** */
int	loc_builtin(t_vars *vars)
{
	print_var(vars->loc);
	return (0);
}

/* ************************************************************************** */
static void add_minishell_to_path(t_vars *vars)
{
	char	*temp_str;
	char	*buff;
	char	temp_cwd[CWD_BUF_SIZE];
	
	buff = ft_strjoin(get_var(vars->env, "PATH")->data, ":");
	getcwd(temp_cwd, CWD_BUF_SIZE);  // free ?
	temp_str = ft_strjoin(buff, temp_cwd);
	ft_free_null((void **)&buff);
	update_var(&vars->env, "PATH", temp_str);
	ft_free_null((void **)&temp_str);
}

/* ************************************************************************** */
