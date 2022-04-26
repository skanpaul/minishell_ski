/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 17:38:49 by gudias           ###   ########.fr       */
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
	t_sig	sig;
}	t_vars;
/* ************************************************************************** */
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

void	exit_builtin(t_vars *vars);
void	echo_builtin(char **cmd_args);
int		pwd_builtin(void);
void	export_builtin(t_vars *vars, char **cmd_args);
void	unset_builtin(t_vars *vars, char **cmd_args);
int		cd_builtin(char *pathname, t_env **ptr_env);
void	env_builtin(t_vars *vars);

void	init_env(t_vars *vars, char **envp);
void	add_to_env(t_vars *vars, char *name, char *data);
t_env	*get_env(t_env *env, char *name);
void	free_env(t_vars *vars);

void	print_maillon(t_env **ptr_env); // SKI
void	replace_env_pwd(t_env **ptr_env, char *new_path); // SKI
void	replace_env_oldpwd(t_env **ptr_env, char *new_path); // SKI

char	*find_cmd_path(t_env *env, char *cmd);
void	run_cmd(t_vars *vars, char *cmd, int output);
void	exec_cmd(t_vars *vars, char *cmd);

void	here_doc(char *limiter);

void	err_msg(char *msg);
void	exit_msg(char *msg);

/* ************************************************************************** */
#endif
