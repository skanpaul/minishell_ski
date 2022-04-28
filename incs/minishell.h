/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/04/28 15:25:06 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* ************************************************************************** */
# include "../libft/includes/libft.h"
# include "errors.h"
/* ************************************************************************** */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
/* ************************************************************************** */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
/* ************************************************************************** */
typedef struct s_sig
{
	//-------------------------------------------
	struct sigaction	sa_sigint_main;
	struct sigaction	sa_sigquit_main;
	//-------------------------------------------
	struct sigaction	sa_signal_prog;

} t_sig;

typedef struct	s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct	s_vars
{
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	t_env	*env;
	t_env	*loc;
	t_sig	sig;
}	t_vars;
/* ************************************************************************** */
# define MSG_SIGINT_MAIN	"\nminishell ski> "
# define MSG_SIGQUIT_MAIN	""
// ----------------------------------------
# define MSG_SIGINT_PROG	"\nCCCC "
# define MSG_SIGQUIT_PROG	"\nDDDD "
/* ************************************************************************** */
void	init_sa_struc_main(t_sig *s);
void	handler_signal_main(int sig_code);
void	init_sigaction_main(t_sig *s);
/* ************************************************************************** */

void	parse_line(t_vars *vars, char *line);

int		is_builtin(char *cmd);
void	exec_builtin(t_vars *vars, char **cmd_args);
int		is_assignation(char *cmd);
void	add_local_var(t_vars *vars, char **cmd_args);

void	exit_builtin(t_vars *vars);

void	echo_builtin(char **cmd_args);
int		pwd_builtin(t_vars *vars);
void	export_builtin(t_vars *vars, char **cmd_args);
void	unset_builtin(t_vars *vars, char **cmd_args);
int		cd_builtin(char *pathname, t_vars *vars);
void	env_builtin(t_vars *vars);
void	loc_builtin(t_vars *vars);
void	init_env(t_vars *vars, char **envp);
void 	init_loc(t_vars *vars);

// -------------------------------------------------------------------
void	write_exit_success(t_vars *vars);
void	write_exit_failure(t_vars *vars);
// -------------------------------------------------------------------
void	print_var(t_env *var_head);
t_env	*get_var(t_env *var_head, char *name);
bool	does_var_exist(t_env *var_head, char *var_name);
void	update_var(t_env **var_head, char *var_name, char *new_data);
void	add_var(t_env **var_head, char *name, char *data);
void	remove_var(t_env **var_head, char *var_name);
void	free_var_list(t_env **var_head);
// -------------------------------------------------------------------

char	*find_cmd_path(t_env *env, char *cmd);
void	run_cmd(t_vars *vars, char *cmd, int output);
void	exec_cmd(t_vars *vars, char *cmd);

void	here_doc(char *limiter);
void	err_quit(int n); // A EFFACER: est utilise dans here_doc.c, mais ou est la definition

void	err_msg(char *msg);
void	exit_msg(char *msg);
int		manage_perror(char *remark, t_vars *vars);
/* ************************************************************************** */
#endif
