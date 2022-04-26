/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ski               #+#    #+#             */
/*   Updated: 2022/04/26 14:28:38 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_var(t_env *var_list)
{
	t_env	*temp;
	
	temp = var_list;
	while (temp)
	{
		ft_putstr_fd(temp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(temp->data, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}	
}

/* ************************************************************************** */
t_env	*get_var(t_env *var_list, char *name)
{
	t_env	*ptr;

	ptr = var_list;
	while (ptr)
	{
		if (!ft_strncmp(name, ptr->name, ft_strlen(name)))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

/* ************************************************************************** */
bool does_var_exist(t_env *var_list, char *var_name)
{
	if (get_var(var_list, var_name) == NULL)
		return (false);
	return (true);
}

/* ************************************************************************** */
void update_var(t_env **var_list, char *var_name, char *new_data)
{
	t_env *buff;

	buff = get_var(*var_list, var_name);
	
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

/* ************************************************************************** */
void	add_var(t_env **var_list, char *name, char *data)
{
	t_env	*ptr;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->name = ft_strdup(name);
	new->data = ft_strdup(data);
	new->next = NULL;
	if (!*var_list)
		*var_list = new;
	else
	{
		ptr = *var_list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

/* ************************************************************************** */
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

/* ************************************************************************** */