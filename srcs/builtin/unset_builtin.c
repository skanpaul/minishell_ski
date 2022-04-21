/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:14:09 by gudias            #+#    #+#             */
/*   Updated: 2022/04/21 18:54:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(t_vars *vars, char *name)
{
	t_env	*ptr;
	t_env	*prev;

	prev = NULL;
	ptr = vars->env;
	while (ptr)
	{
		if (!ft_strncmp(name, ptr->name, ft_strlen(ptr->name)))
		{
			if (prev)
				prev->next = ptr->next;
			else
				vars->env = ptr->next;
			free(ptr->name);
			free(ptr->data);
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;	
	}
}
