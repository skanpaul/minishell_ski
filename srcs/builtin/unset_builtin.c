/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:14:09 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 18:01:29 by gudias           ###   ########.fr       */
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
		//sera remplacer par la fonction remove_var
    //remove_var(&vars->env, name);
		//il faudra supprimer aussi dans var_loc
		prev = NULL;
		ptr = vars->env;
		while (ptr)
		{
			if (!ft_strncmp(cmd_args[i], ptr->name, ft_strlen(ptr->name) + 1))
			{
				if (prev)
					prev->next = ptr->next;
				else
					vars->env = ptr->next;
				free(ptr->name);
				free(ptr->data);
				free(ptr);
				break ;
			}
			prev = ptr;
			ptr = ptr->next;	
		}
		i++;
	}
}
