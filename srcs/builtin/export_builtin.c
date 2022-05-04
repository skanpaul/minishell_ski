/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/04 16:26:03 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_vars *vars, char **cmd_args)
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
			if (does_var_exist(vars->loc, name))
				data = ft_strdup(get_var(vars->loc, name)->data);
			else
				data = NULL;
		}
		if (ft_strlen(name) < 1) //check name_is_valid (char special, chiffre, etc..)
		{
			err_msg("export: not a valid identifier");
			return (1);
		}
		else
			update_var(&vars->env, name, data); 
  
		if (does_var_exist(vars->loc, name))
				update_var(&vars->loc, name, data);
    
		ft_free_null((void**)&data);
		ft_free_null((void**)&name);      
		i++;
	}
	return (0);
}	
