/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:48:06 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 17:43:08 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexing(t_vars *vars, char *line)
{
	int		i;
	char	**segments;

	segments = NULL;
	if (is_grammar_correct(line, vars))
	{
		line = chevron_space_maker(line);
		line = pipeline_space_maker(line);
		segments = split_shell_line(line, '|');
		i = -1;
		while (segments[++i])
			vars->segments_count++;
		vars->new_line = line;
	}
	return (segments);
}
