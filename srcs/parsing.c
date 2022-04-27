/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 22:18:12 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_vars *vars, char *line)
{
	char	**cmd_args;
	
	//check single quotes

	//check double quotes
	
	//check redirs

	//replace $value

	cmd_args = ft_split(line, ' ');
	if (!cmd_args[0])
		return ;
	add_history(line);
	if (is_builtin(cmd_args[0]))
		exec_builtin(vars, cmd_args);
	else
		run_cmd(vars, line, 1);
	
	ft_free_array(cmd_args);
}
