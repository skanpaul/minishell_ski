/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:07:30 by gudias            #+#    #+#             */
/*   Updated: 2022/05/18 18:32:05 by gudias           ###   ########.fr       */
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

void	get_redirections(t_vars *vars, char **cmd_args, int *fd_in, int *fd_out, int output)
{	
	*fd_in = 0;
	*fd_out = 0;
	*fd_in = get_segment_fd_in(vars, cmd_args);
	*fd_out = get_segment_fd_out(cmd_args);
	clear_chevron_segment(cmd_args);
	if (*fd_in)
		redirect_input(*fd_in);
	if (*fd_out)
		redirect_output(*fd_out);
	else	
		*fd_out = output;
}
