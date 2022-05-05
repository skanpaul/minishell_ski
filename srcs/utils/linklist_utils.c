/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 08:48:42 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void print_var(t_env *var_head)
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
bool does_var_exist(t_env *var_head, char *var_name)
{
	if (get_var(var_head, var_name) == NULL)
		return (false);
	return (true);
}

/* ************************************************************************** */
void update_var(t_env **var_head, char *var_name, char *new_data)
{
	t_env *buff;

	buff = NULL;
	
	if (!does_var_exist(*var_head, var_name))
		add_var(var_head, var_name, new_data);
	else
	{
		buff = get_var(*var_head, var_name);
		ft_free_null((void**)&buff->data);
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
void remove_var(t_env **var_head, char *var_name)
{
	t_env	*ptr;
	t_env	*prev;

	prev = NULL;
	ptr = *var_head;
	while (ptr)
	{
		if (!ft_strncmp(var_name, ptr->name, ft_strlen(ptr->name) + 1))
		{
			if (prev)
				prev->next = ptr->next;
			else
				*var_head = ptr->next;
			ft_free_null((void**)&ptr->name);
			ft_free_null((void**)&ptr->data);
			ft_free_null((void**)&ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;	
	}
}

/* ************************************************************************** */
int size_var_list(t_env *var_head)
{
	int i;
	t_env *temp;
	
	temp = var_head;

	i = 0;
	while(temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
void	free_var_list(t_env **var_head)
{
	t_env	*tmp;
	t_env	*ptr;

	ptr = *var_head;
	while (ptr)
	{
		ft_free_null((void**)&ptr->name);
		ft_free_null((void**)&ptr->data);
		tmp = ptr->next;
		ft_free_null((void**)&ptr);
		ptr = tmp;
	}
	*var_head = NULL;
}

/* ************************************************************************** */
