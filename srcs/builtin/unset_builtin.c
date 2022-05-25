/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:14:09 by gudias            #+#    #+#             */
/*   Updated: 2022/05/25 16:23:29 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_vars *vars, char **cmd_args)
{
	int	i;
	int	return_code;

	return_code = 0;
	i = 1;
	while (cmd_args[i])
	{
		if (!name_is_valid(cmd_args[i]))
		{
			err_msg(ERR_UNSET_ID);
			return_code = 1;
		}
		else
		{
			remove_var(&vars->env, cmd_args[i]);
			remove_var(&vars->loc, cmd_args[i]);
		}
		i++;
	}
	return (return_code);
}
