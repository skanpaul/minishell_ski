/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 12:54:19 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(t_env **child_env, char **parent_env)
{
	char	*name;
	char	*data;
	int		len;
	t_env	*temp;

	while (*parent_env)
	{
		len = ft_strchr(*parent_env, '=') - *parent_env;
		name = ft_substr(*parent_env, 0, len);
		data = ft_substr(*parent_env, len + 1, ft_strlen(*parent_env));
		add_var(child_env, name, data);
		free(name);
		free(data);
		parent_env++;
	}

	//assurer que PATH, HOME, PWD, OLDPWD, SHLVL SONT PRESENTS
	//sinon -> les ajouter
	
	temp = get_env(*child_env, "SHLVL");
	temp->data = ft_itoa(ft_atoi(temp->data) + 1);
}

void	env_builtin(t_vars *vars)
{
	print_var(vars->env);
}
