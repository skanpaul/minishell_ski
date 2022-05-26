/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:19:45 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/26 18:30:23 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
// return FALSE if general grammar is not correct
bool	is_grammar_correct(char *line, t_vars *vars)
{
	char	*cpy_line;

	cpy_line = ft_strdup(line);
	if (is_line_with_correct_quote(cpy_line, vars))
	{
		cpy_line = chevron_space_maker(cpy_line);
		cpy_line = pipeline_space_maker(cpy_line);
		if (is_grammar_pipeline_correct(cpy_line, vars)
			&& is_grammar_chevron_correct(cpy_line, vars))
		{
			ft_free_null(&cpy_line);
			return (true);
		}
	}		
	ft_free_null(&cpy_line);
	return (false);
}

/* ************************************************************************** */
// return NULL if general grammar is not correct
// !!! WARNING !!!: exit the main program if NULL is returned
// char    *check_grammar(char *line, t_vars *vars)
// {
// 	if (!line)
// 		return (NULL);	
// 	line = check_grammar_pipeline(line, vars);
// 	if (!line)
// 		return (line);		
// 	line = check_grammar_chevron(line, vars);
// 	if (!line)
// 		return (line);
//     return (line);
// }
/* ************************************************************************** */