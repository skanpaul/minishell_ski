/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ski               #+#    #+#             */
/*   Updated: 2022/04/25 17:04:31 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_vars *vars)
{
	t_env	*tmp;
	t_env	*ptr;

	ptr = vars->env;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->data);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

void	add_to_env(t_vars *vars, char *name, char *data)
{
	t_env	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->data = ft_strdup(data);
	new->next = NULL;
	if (!vars->env)
		vars->env = new;
	else
	{
		ptr = vars->env;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_env	*get_env(t_env *env, char *name)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (!ft_strncmp(name, ptr->name, ft_strlen(name)))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_env **get_env_var_ptr(t_env **ptr_env, char *wished_var)
{
	t_env **temp;

	temp = ptr_env;

	while (*temp != NULL)
	{
		if(ft_strncmp((*temp)->name, wished_var, ft_strlen(wished_var)) == 0)
		{
			return (temp);
		}
		temp = &(*temp)->next;
	}
	
	return (NULL);
}

void update_var(t_env **ptr_env, char *var_name, char *new_data)
{
	t_env **buff;

	buff = get_env_var_ptr(ptr_env, var_name);
	
	if (*buff == NULL)
	{
		printf("[ %s ] n'existe pas\n", var_name);	
	}
	else
	{
		free((*buff)->data);
		(*buff)->data = ft_strdup(new_data);
	}	
}