/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:59:35 by ski               #+#    #+#             */
/*   Updated: 2022/05/23 14:58:18 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
char 	**conv_list_to_array(t_env *var_head)
{
	int i;
	char *start_string;
	int size_list;
	char **env_char_array;
	
	start_string = NULL;
	env_char_array = NULL;
	size_list = size_var_list(var_head);
	
	if (size_list == 0)
		return (env_char_array);

	env_char_array = (char **)malloc(size_list * (sizeof(char *) + 1));
	env_char_array[size_list] = NULL;

	i = 0;
	while (i < size_list)
	{
		start_string = ft_strjoin(var_head->name, "=");		
		env_char_array[i] = ft_strjoin(start_string, var_head->data);
		ft_free_null((void*)&start_string);		
		var_head = var_head->next;
		i++;
	}

	return (env_char_array);	
}

/* ************************************************************************** */
void print_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putstr(array[i]);
		ft_putstr("\n");
		i++;
	}
}

/* ************************************************************************** */
void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_free_null((void*)&array[i]);
		i++;
	}

	if (array)
		free(array);
	array = NULL;
}

/* ************************************************************************** */
