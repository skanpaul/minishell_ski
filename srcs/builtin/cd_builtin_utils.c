/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:35:13 by ski               #+#    #+#             */
/*   Updated: 2022/04/20 20:22:20 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
#define START_PWD		"PWD="
#define START_OLDPWD	"OLDPWD="

/* ************************************************************************** */
static void			replace_env_var(t_maillon **ptr_env, char *env_var, char *path);
static t_maillon	**get_env_var_ptr(t_maillon **ptr_env, char *wished_var);
/* ************************************************************************** */
void print_maillon(t_maillon **ptr_head)
{
	t_maillon *temp;

	temp = *ptr_head;

	while(temp != NULL)
	{
		printf("%s\n", temp->var_env);
		temp = temp->next;		
	}
	printf("\n");
}
/* ************************************************************************** */
void replace_env_pwd(t_maillon **ptr_env, char *new_path)
{
	replace_env_var(ptr_env, "PWD=", new_path);
}
/* ************************************************************************** */
void replace_env_oldpwd(t_maillon **ptr_env, char *new_path)
{
	replace_env_var(ptr_env, "OLDPWD=", new_path);
}

/* ************************************************************************** */
void replace_env_var(t_maillon **ptr_env, char *env_var, char *path)
{
	t_maillon **env_pwd;

	env_pwd = get_env_var_ptr(ptr_env, env_var);
	
	if (*env_pwd == NULL)
	{
		printf("[ %s ] n'existe pas\n", env_var);	
	}
	else
	{
		free((*env_pwd)->var_env);
		(*env_pwd)->var_env = ft_strjoin(env_var, path);
	}	
}

/* ************************************************************************** */
t_maillon **get_env_var_ptr(t_maillon **ptr_env, char *wished_var)
{
	t_maillon **temp;

	temp = ptr_env;

	while (*temp != NULL)
	{
		if(ft_strncmp((*temp)->var_env, wished_var, ft_strlen(wished_var)) == 0)
		{
			return (temp);
		}
		temp = &(*temp)->next;
	}
	
	return (NULL);
}

/* ************************************************************************** */