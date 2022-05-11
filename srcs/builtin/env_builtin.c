/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/11 09:07:03 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*temp_env;
	char	*temp_str;

	temp_env = 0;
	temp_str = 0;

	copy_parent_env(&vars->env, envp);
	
	// Update: SHLVL
	temp_env = get_var(vars->env, "SHLVL");
	temp_str = ft_itoa(ft_atoi(temp_env->data) + 1);	
	ft_free_null((void **)&temp_env->data);	
	temp_env->data = temp_str;

	// AJOUTER le path de [./minishell] dans la variable d'environnement $PATH
	
	remove_var(&vars->env, "OLDPWD");
	
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
