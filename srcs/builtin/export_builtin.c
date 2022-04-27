/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 21:09:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_builtin(t_vars *vars, char **cmd_args)
{
	char	*name;
	char	*equal;
	char	*data;
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (equal)
		{
			name = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);	
			data = ft_substr(equal, 1, ft_strlen(equal + 1));
		}
		else
		{
			name = ft_strdup(cmd_args[i]); 
			data = NULL;//check data in local_vars
		}
		if (ft_strlen(name) < 1)
			err_msg("export: not a valid identifier");
		else if (data)
		{
			if (get_env(vars->env, name))
			{
				free(get_env(vars->env, name)->data);
				get_env(vars->env, name)->data = ft_strdup(data);
			}
			else
				add_to_env(vars, name, data);
		}	
		free(data);
		free(name);
		i++;
	}
}	
