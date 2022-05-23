/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:29:38 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 14:15:27 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	execute_cmd(t_vars *vars, t_cmd *cmd, int i)
{
	int		return_code;

	return_code = 0;
	if (cmd->fd_in)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out > 1)
		dup2(cmd->fd_out, 1);
	//execute cmds
	translate_dollars_all(cmd->args, vars);
	if (cmd->args[i] && vars->segments_count == 1 && is_builtin(cmd->args[i]))
		return_code = exec_builtin(vars, (cmd->args) + i);
	else
		return_code = run_cmd(vars, (cmd->args) + i, cmd->fd_out);
	return (return_code);
}
