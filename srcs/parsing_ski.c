/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ski.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:44:42 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 10:52:30 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void translate_dollar_on_1_token(char *token, t_vars *vars);

/* ************************************************************************** */
char **parsing_ski(t_vars *vars, char *line)
{
	char **token_array;

	token_array = NULL;
	(void)vars;

	line = chevron_space_maker(line);
	line = pipeline_space_maker(line);

	token_array = split_shell_line(line, ' ');		
						
	return (token_array);
}

	// ft_printf("space maker APRES: %s\n", line);
	// ft_printf("\n");

	// cnt_w = count_words(line, ' ');
	// ft_printf("count word: [%d]\n", cnt_w);
	
/* ************************************************************************** */
// static void translate_dollar_on_1_token(char *token, t_vars *vars)
// {
// 	int i;
// 	t_quote_info qti;

// 	init_quote_info(&qti);

// 	i = 0;
// 	while (token[i] != 0)
// 	{
// 		refresh_quote_info(&qti, token[i]);
		

// 		i++;
// 	}	
// }

/* ************************************************************************** */