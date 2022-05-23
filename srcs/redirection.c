/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:07:30 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 14:17:17 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input(int new_fd)
{	
		dup2(new_fd, 0);
}

static void	redirect_output(int new_fd)
{
		dup2(new_fd, 1);
}


void	get_redirections(t_vars *vars, t_cmd *cmd)
{	
	cmd->fd_in = get_segment_fd_in(vars, cmd->args);
	cmd->fd_out = get_segment_fd_out(cmd->args);
	clear_chevron_segment(cmd->args);
}

void	reset_redirections(t_vars *vars, t_cmd *cmd)
{
	if (cmd->fd_in)
		close (cmd->fd_in);
	if (cmd->fd_out > 1)
	{
		dup2(vars->stdout_fd, 1);
		close (cmd->fd_out);
	}
}
