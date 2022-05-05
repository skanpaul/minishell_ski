/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/05/05 14:24:55 by ski              ###   ########.fr       */
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
#include <dirent.h>
/* ************************************************************************** */
typedef struct s_quote_info
{
	int		cnt_char_realquote;
	char	last_char_realquote;
	bool	flag_inside_realquote;
	bool	flag_entering_realquote;
	bool	flag_exiting_realquote;
	
}	t_quote_info;
// ----------------------------------------
typedef struct s_sig
{
	struct sigaction	sa_sigint_main;
	struct sigaction	sa_sigquit_main;
	struct sigaction	sa_signal_prog;
} t_sig;
// ----------------------------------------
typedef struct	s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;
// ----------------------------------------
typedef struct	s_vars
{
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	t_env	*env;
	t_env	*loc;
	char	**env_char_array;
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
void	initialisation(t_vars *vars, char **envp);
void	clean_program(t_vars *vars);
/* ************************************************************************** */


void	parse_line(t_vars *vars, char *line);
char	*replace_vars(t_vars *vars, char *line);

char 	**parsing_ski(t_vars *vars, char *line);

int		is_builtin(char *cmd);
void	exec_builtin(t_vars *vars, char **cmd_args);
int		is_assignation(char *cmd);
void	add_local_var(t_vars *vars, char **cmd_args);

void	exit_builtin(t_vars *vars);

void	echo_builtin(char **cmd_args);
int		pwd_builtin(t_vars *vars, char **cmd_args);
void	export_builtin(t_vars *vars, char **cmd_args);
void	unset_builtin(t_vars *vars, char **cmd_args);
int		cd_builtin(t_vars *vars, char **cmd_args);
void	env_builtin(t_vars *vars);
void	loc_builtin(t_vars *vars);
void	init_env(t_vars *vars, char **envp);
void 	init_loc(t_vars *vars);

// ------------------------------------------------------ temporaire.c
void	write_exit_success(t_vars *vars);
void	write_exit_failure(t_vars *vars);
// ------------------------------------------------------ temporaire.c
bool	does_word_match(char *str, char *hard_text);
void	ft_free_null(void **ptr);
// ------------------------------------------------ cd_builtin_utils.c
char	*manage_tild(char *pathname, t_vars *vars);
bool	is_good_path(char *pathname, t_vars *vars);
// -------------------------------------------------- linklist_utils.c
void	print_var(t_env *var_head);
t_env	*get_var(t_env *var_head, char *var_name);
bool	does_var_exist(t_env *var_head, char *var_name);
void	update_var(t_env **var_head, char *var_name, char *new_data);
void	add_var(t_env **var_head, char *name, char *data);
void	remove_var(t_env **var_head, char *var_name);
int		size_var_list(t_env *var_head);
void	free_var_list(t_env **var_head);
// ----------------------------------------------------- array_utils.c
char	**conv_list_to_array(t_env *var_head);
void	print_array(char **array);
void	free_array(char **array);
// -------------------------------------------------------------------
char	**split_shell_line(char *line, char separator);
int		count_words(char *line, char separator);
char	*chevron_space_maker(char *line);
char	*pipeline_space_maker(char *line);
// ------------------------------------------------ translate_dollar.c
void translate_dollar_all_token(char **token_array, t_vars *vars);
// char *translate_dollar_1_token(char *token, t_vars *vars);
void translate_dollar_1_token(char **token, t_vars *vars);
bool is_dollar_variable(char *ptr_dollar);
// ------------------------------------------------ quote_info_utils.c
void	init_quote_info(t_quote_info *qti);
void	refresh_quote_info(t_quote_info *qti, char actual_char);
bool	is_good_number_of_realquote(t_quote_info *qti);
bool	is_inside_realquote(t_quote_info *qti);
bool	is_outside_realquote(t_quote_info *qti);
bool	is_entering_realquote(t_quote_info *qti);
bool	is_exiting_realquote(t_quote_info *qti);
bool	is_inside_double_realquote(t_quote_info *qti);
bool	is_inside_single_realquote(t_quote_info *qti);

bool 	is_line_with_correct_quote(char *line);
// -------------------------------------------------------------------
void	ft_add_history(char *new_line);
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
