/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/02 12:31:47 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_vars *vars, char *line)
{
	char	**cmd_args;
	
	//check space: [ ... >file ] vs. [ ... > file ]
	
	//check single quotes

	//check double quotes
	
	//check redirs

	//replace $value

	cmd_args = ft_split(line, ' ');
	if (!cmd_args[0])
		return ;
	add_history(line);
	if (is_builtin(cmd_args[0]))
	{
		write_exit_success(vars);	
		exec_builtin(vars, cmd_args);
	}
	else
	{
		write_exit_success(vars);
		run_cmd(vars, line, 1);
	}
	ft_free_array(cmd_args);
}
