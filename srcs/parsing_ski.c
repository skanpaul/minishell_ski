/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ski.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:44:42 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 11:42:26 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void translate_dollar_all_token(char **token_array, t_vars *vars);
// static char *translate_dollar_1_token(char *token, t_vars *vars);
static void translate_dollar_1_token(char **token, t_vars *vars);

/* ************************************************************************** */
char **parsing_ski(t_vars *vars, char *line)
{
	char **token_array;

	token_array = NULL;
	(void)vars;

	line = chevron_space_maker(line);
	line = pipeline_space_maker(line);

	token_array = split_shell_line(line, ' ');

	translate_dollar_all_token(token_array, vars);		
						
	return (token_array);
}

	// ft_printf("space maker APRES: %s\n", line);
	// ft_printf("\n");

	// cnt_w = count_words(line, ' ');
	// ft_printf("count word: [%d]\n", cnt_w);
	
/* ************************************************************************** */
static void translate_dollar_1_token(char **token, t_vars *vars)
{
	int i;
	t_quote_info qti;

	init_quote_info(&qti);
	
	i = 0;
	while ((*token)[i] != 0)
	{
		refresh_quote_info(&qti, (*token)[i]);



		
		// code manquant
		
		
		
		i++;
	}

}

/* ************************************************************************** */
// static char *translate_dollar_1_token(char *token, t_vars *vars)
// {
// 	token = replace_vars(vars, token);	
// 	return (token);
// }

/* ************************************************************************** */
static void translate_dollar_all_token(char **token_array, t_vars *vars)
{
	int i;

	i = 0;
	while (token_array[i] != NULL)
	{
		translate_dollar_1_token(&token_array[i], vars);
		i++;	
	}	
}

/* ************************************************************************** */
static bool is_dollar_variable(char *ptr_dollar)
{
	if (ptr_dollar[1] != ' ' || ptr_dollar[1] != '\'' || ptr_dollar[1] != '\"')
		return (false);
	return (true);
}

/* ************************************************************************** */