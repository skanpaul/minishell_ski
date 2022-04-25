/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/04/25 19:29:21 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_vars *vars, char *line)
{
	char	**cmd_args;

	cmd_args = ft_split(line, ' ');

	if (is_builtin(cmd_args[0]))
		exec_builtin(vars, line);
	else
		run_cmd(vars, line, 1);

	//free_array(cmd_args);
}
