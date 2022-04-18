/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/04/18 10:43:49 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include "errors.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_vars
{
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
}			t_vars;

char	*get_path(char **envp);
char	*find_cmd_path(char *cmd, char **envp);
void	run_cmd(t_vars *vars, char *cmd, char **envp, int output);
void	exec_cmd(char *cmd, char **envp);

void	here_doc(char *limiter);

void	err_msg(char *msg);
void	exit_msg(char *msg);

#endif
