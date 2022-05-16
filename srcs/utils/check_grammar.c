/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:19:45 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/16 16:01:13 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
// return NULL if general grammar is not correct
// !!! WARNING !!!: exit the main program if NULL is returned
char    *check_grammar(char *line, t_vars *vars)
{
	// if (!is_line_with_correct_quote(line))
	// 	return (NULL);	
	
	// line = chevron_space_maker(line);
	// line = pipeline_space_maker(line);
	if (!line)
		return (NULL);
	
	line = check_grammar_pipeline(line, vars);
	if (!line)
		return (line);
		
	line = check_grammar_chevron(line, vars);
	if (!line)
		return (line);

    return (line);
}

/* ************************************************************************** */