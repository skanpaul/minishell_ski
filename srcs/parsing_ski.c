/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ski.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:44:42 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 15:03:55 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
char **parsing_ski(t_vars *vars, char *line)
{
	int cnt_w;
	char **token_array;

	token_array = NULL;
	(void)vars;

	line = chevron_space_maker(line);
	line = pipeline_space_maker(line);

	// ft_printf("-------------------------------------\n");
	ft_printf("APRES (space maker): %s\n", line);

	token_array = split_shell_line(line, ' ');

	// cnt_w = count_words(line, ' ');
	// ft_printf("count word: [%d]\n", cnt_w);
	// ft_printf("-------------------------------------\n");
	// ft_printf("\n");
	// ft_printf("-------------------------------------\n");

	translate_dollar_all_token(token_array, vars);
	
	// ft_printf("APRES (dollar_translate): %s\n", line);
	// ft_printf("\n");
	// ft_printf("-------------------------------------\n");		
						
	return (token_array);
}

/* ************************************************************************** */