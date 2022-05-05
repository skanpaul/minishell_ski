/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ski.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:44:42 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 10:07:44 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
/* ************************************************************************** */

	// ft_printf("space maker APRES: %s\n", line);
	// ft_printf("\n");

	// cnt_w = count_words(line, ' ');
	// ft_printf("count word: [%d]\n", cnt_w);