/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:14:09 by gudias            #+#    #+#             */
/*   Updated: 2022/04/27 16:19:17 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(t_vars *vars, char **cmd_args)
{
	t_env	*ptr;
	t_env	*prev;
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		//il faudra supprimer aussi dans var_loc
	
    	remove_var(&vars->env, cmd_args[i]);

		i++;
	}
}
