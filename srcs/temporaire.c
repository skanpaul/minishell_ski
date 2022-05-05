/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:18:13 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 09:50:32 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void init_loc(t_vars *vars)
{
	write_exit_success(vars);
}

/* ************************************************************************** */
void write_exit_success(t_vars *vars)
{
	update_var(&vars->loc, "?", EXIT_SUCCESS_STR);
}

/* ************************************************************************** */
void write_exit_failure(t_vars *vars)
{
	update_var(&vars->loc, "?", EXIT_FAILURE_STR);
}

/* ************************************************************************** */
bool does_word_match(char *str, char *hard_text)
{
	int res;

	res = ft_strncmp(str, hard_text, ft_strlen(hard_text) + 1);
	if (res == 0)
		return (true);
	return (false);	
}
/* ************************************************************************** */
void ft_free_null(void **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

/* ************************************************************************** */
void ft_add_history(char *new_line)
{
	if (new_line[0] != '\0' || new_line != NULL)
		add_history(new_line);
}

/* ************************************************************************** */
char *dollar_translate(t_vars *vars, char *dollar_var)
{
	char *var_name;

	// var_name = foreign_word;		// exclus le signe $
	var_name = dollar_var + 1;	// inclus le signe $   
		
	if (does_var_exist(vars->env, var_name))
		return (get_var(vars->env, var_name)->data);

	if (does_var_exist(vars->loc, var_name))
		return (get_var(vars->loc, var_name)->data);

	return (NULL);
}

/* ************************************************************************** */

