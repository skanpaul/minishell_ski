/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ski               #+#    #+#             */
/*   Updated: 2022/05/26 18:30:23 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	print_var(t_env *var_head)
{
	t_env	*temp;

	temp = var_head;
	while (temp)
	{
		if (!temp->data)
			return ;
		ft_putstr_fd(temp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(temp->data, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}	
}

/* ************************************************************************** */
t_env	*get_var(t_env *var_head, char *var_name)
{
	t_env	*ptr;

	ptr = var_head;
	while (ptr)
	{
		if (!ft_strncmp(var_name, ptr->name, ft_strlen(ptr->name) + 1))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/* ************************************************************************** */
bool	does_var_exist(t_env *var_head, char *var_name)
{
	if (get_var(var_head, var_name) == NULL)
		return (false);
	return (true);
}

/* ************************************************************************** */
// update_var():
//		- free itself the old_data
//		- malloc itself the new_data
// ---------------------------------------------------------------
void	update_var(t_env **var_head, char *var_name, char *new_data)
{
	t_env	*buff;

	buff = NULL;
	if (!does_var_exist(*var_head, var_name))
		add_var(var_head, var_name, new_data);
	else
	{
		buff = get_var(*var_head, var_name);
		ft_free_null(&buff->data);
		buff->data = ft_strdup(new_data);
	}	
}

/* ************************************************************************** */
void	add_var(t_env **var_head, char *name, char *data)
{
	t_env	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	if (data)
		new->data = ft_strdup(data);
	else
		new->data = NULL;
	new->next = NULL;
	if (!*var_head)
		*var_head = new;
	else
	{
		ptr = *var_head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

/* ************************************************************************** */