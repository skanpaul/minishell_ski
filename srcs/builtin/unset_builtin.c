/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:14:09 by gudias            #+#    #+#             */
/*   Updated: 2022/05/04 16:21:13 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_vars *vars, char **cmd_args)
{
	// t_env	*ptr;
	// t_env	*prev;
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		//check name, "not a valid identifier" --> return (1)
		//ne doit pas commencer par un chiffre, pas de char special
		//++ ??
		//surement meme checks que pour assign (name_is_valid)

    		remove_var(&vars->env, cmd_args[i]);
    		remove_var(&vars->loc, cmd_args[i]);
		i++;
	}
	return (0);
}
