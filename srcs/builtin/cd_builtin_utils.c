/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:35:13 by ski               #+#    #+#             */
/*   Updated: 2022/04/21 15:32:22 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
#define START_PWD		"PWD="
#define START_OLDPWD	"OLDPWD="

/* ************************************************************************** */
static void		replace_env_var(t_env **ptr_env, char *var_name, char *path);
static t_env	**get_env_var_ptr(t_env **ptr_env, char *wished_var);
/* ************************************************************************** */
void print_maillon(t_env **ptr_head)
{
	t_env *temp;

	temp = *ptr_head;

	while(temp != NULL)
	{
		printf("%s=", temp->name);
		printf("%s\n", temp->data);
		temp = temp->next;		
	}
	printf("\n");
}
/* ************************************************************************** */
void replace_env_pwd(t_env **ptr_env, char *new_path)
{
	replace_env_var(ptr_env, "PWD", new_path);
}
/* ************************************************************************** */
void replace_env_oldpwd(t_env **ptr_env, char *new_path)
{
	replace_env_var(ptr_env, "OLDPWD", new_path);
}

/* ************************************************************************** */
void replace_env_var(t_env **ptr_env, char *var_name, char *path)
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
		(*buff)->data = ft_strdup(path);
	}	
}

/* ************************************************************************** */
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

/* ************************************************************************** */