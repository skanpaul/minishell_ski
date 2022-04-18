/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/04/18 14:43:02 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/includes/libft.h"
# include "errors.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
/* ************************************************************************** */

typedef struct	s_vars
{
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
}			t_vars;

/* ************************************************************************** */
typedef struct s_data
{
	char				*new_line;
	//-------------------------------------------
	struct sigaction	sa_sigint_main;
	struct sigaction	sa_sigquit_main;
	//-------------------------------------------
	struct sigaction	sa_signal_prog;
	//-------------------------------------------
	pid_t	pid_parent;
	pid_t	pid_process;
	pid_t	pid_child;


} t_data;
/* ************************************************************************** */
# define MSG_SIGINT_MAIN	"\nminishell ski> "
# define MSG_SIGQUIT_MAIN	""
// # define MSG_SIGQUIT_MAIN	"\rski_shell> "
// ----------------------------------------
# define MSG_SIGINT_PROG	"\nCCCC "
# define MSG_SIGQUIT_PROG	"\nDDDD "
/* ************************************************************************** */
void	init_sa_struc_main(t_data *d);
void	handler_signal_main(int sig_code);
void	init_sigaction_main(t_data *d);
/* ************************************************************************** */

char	*get_path(char **envp);
char	*find_cmd_path(char *cmd, char **envp);
void	run_cmd(t_vars *vars, char *cmd, char **envp, int output);
void	exec_cmd(char *cmd, char **envp);

void	here_doc(char *limiter);

void	err_msg(char *msg);
void	exit_msg(char *msg);

/* ************************************************************************** */
#endif
