/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/27 17:31:33 by ski              ###   ########.fr       */
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
			data = get_var(vars->loc, name)->data;
		}
		if (ft_strlen(name) < 1)
			err_msg("export: not a valid identifier");
		else if (data) //enlever data?
			update_var(&vars->env, name, data);
		free(data);
		free(name);
		i++;
	}
}	
