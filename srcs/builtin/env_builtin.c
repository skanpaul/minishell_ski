/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/21 17:48:40 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_vars *vars)
{
	t_env	*tmp;
	t_env	*ptr;

	ptr = vars->env;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->data);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void	add_to_env(t_vars *vars, char *name, char *data)
{
	t_env	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->data = ft_strdup(data);
	new->next = NULL;
	if (!vars->env)
		vars->env = new;
	else
	{
		ptr = vars->env;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env	*get_env(t_env *env, char *name)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(name, ptr->name, ft_strlen(name)))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void	init_env(t_vars *vars, char **envp)
{
	char	*name;
	char	*data;
	int	len;

	while (*envp)
	{
		len = ft_strchr(*envp, '=') - *envp;
		name = ft_substr(*envp, 0, len);
		data = ft_substr(*envp, len + 1, ft_strlen(*envp));
		add_to_env(vars, name, data);
		free(name);
		free(data);
		envp++;
	}
	//assurer que PATH, HOME, PWD, OLDPWD, SHLVL SONT PRESENTS
	//sinon -> les ajouter
}

void	env_builtin(t_vars *vars)
{
	t_env	*env;

	env = vars->env;
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->data, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}