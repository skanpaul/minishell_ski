/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:11:34 by gudias            #+#    #+#             */
/*   Updated: 2022/05/25 12:49:35 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_input(char *limiter, int pipe_fd[2])
{
	char	*rd_line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	close(pipe_fd[0]);
	while (1)
	{
		write(1, "here_doc> ", 10);
		rd_line = get_next_line(0);
		if (!rd_line)
		{
			close(pipe_fd[1]);
			exit(1);
		}
		if (rd_line[limiter_len] == '\n' && \
			!ft_strncmp(limiter, rd_line, limiter_len))
		{
			free(rd_line);
			close(pipe_fd[1]);
			exit(0);
		}
		write(pipe_fd[1], rd_line, ft_strlen(rd_line));
		free(rd_line);
	}
}

void	here_doc(char *limiter)
{
	int		id;
	int		pipe_fd[2];
	t_sig	s;

	if (pipe(pipe_fd) == -1)
		err_msg(ERR_PIPE);
	id = fork();
	if (id == -1)
		err_msg(ERR_FORK);
	if (id == 0)
	{
		init_signal_fork_child_hd(&s);
		pipe_input(limiter, pipe_fd);
	}	
	init_signal_fork_parent(&s);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	waitpid(id, NULL, 0);
	init_signal_main(&s);
}

/* ************************************************************************** */
