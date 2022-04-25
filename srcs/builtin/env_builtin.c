/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/25 16:32:23 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
