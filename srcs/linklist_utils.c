/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ski               #+#    #+#             */
/*   Updated: 2022/04/26 13:05:30 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_var_list(t_env **var_list)
{
	t_env	*tmp;
	t_env	*ptr;

	ptr = *var_list;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->data);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*var_list = NULL;
}

t_env	*get_var(t_env *env, char *name)
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

void	add_var(t_env **var_table, char *name, char *data)
{
	t_env	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->data = ft_strdup(data);
	new->next = NULL;
	if (!*var_table)
		*var_table = new;
	else
	{
		ptr = *var_table;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void print_var(t_env *ptr_var)
{
	t_env	*temp;
	
	temp = ptr_var;
	while (temp)
	{
		ft_putstr_fd(temp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(temp->data, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}	
}

void update_var(t_env **ptr_var_table, char *var_name, char *new_data)
{
	t_env *buff;

	buff = get_var(*ptr_var_table, var_name);
	
	if (buff == NULL)
	{
		printf("[ %s ] n'existe pas\n", var_name);	
	}
	else
	{
		free(buff->data);
		buff->data = ft_strdup(new_data);
	}	
}