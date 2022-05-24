/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 11:49:09 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* ************************************************************************** */
# include "../libft/includes/libft.h"
# include "errors.h"
# include "colors.h"
/* ************************************************************************** */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
/* ************************************************************************** */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <termios.h>
/* ************************************************************************** */

typedef struct s_quote_info
{
	int		cnt_char_realquote;
	char	last_char_realquote;
	bool	flag_inside_realquote;
	bool	flag_entering_realquote;
	bool	flag_exiting_realquote;
	
}	t_quote_info;

/* ************************************************************************** */

typedef struct s_sig
{
	struct sigaction	sa_sigint;	// ctrl-C
	struct sigaction	sa_sigquit;	// ctrl-/
	struct sigaction	sa_sigchild;
	// struct sigaction	sa_sig_ctr_D;
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
	char	*new_line;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	t_env	*env;
	t_env	*loc;
	char	**env_char_array; // à effacer ?
	t_sig	sig;
	int		segments_count;
}	t_vars;

/* ************************************************************************** */

typedef struct	s_cmd
{
	int	fd_in;
	int	fd_out;
	char	**args;
}	t_cmd;

/* ************************************************************************** */
void	init_signal_main(t_sig *s);
void	handler_signal_main(int sig_code);
// --------------------------------------------
void	init_signal_fork_child(t_sig *s);
// void	handler_signal_fork_child(int sig_code);
// --------------------------------------------
void	init_signal_fork_parent(t_sig *s);
void	handler_signal_fork_parent(int sig_code);
/* ************************************************************************** */
void	initialisation(t_vars *vars, char **envp);
void	clean_program(t_vars *vars);
/* ************************************************************************** */
char	**lexing(t_vars *vars, char * line);
void	handle_segments(t_vars *vars, char **segments);
void	parse_line(t_vars *vars, char *line, int output);
int	check_assignation(t_vars *vars, t_cmd *cmd);

int		execute_cmd(t_vars *vars, t_cmd *cmd, int i);
void	get_redirections(t_vars *vars, t_cmd *cmd);
void	reset_redirections(t_vars *vars, t_cmd *cmd);

int		is_builtin(char *cmd);
int		exec_builtin(t_vars *vars, char **cmd_args);
int		is_assignation(char *cmd);
int		name_is_valid(char *name);
int		add_local_var(t_vars *vars, char **cmd_args);

int		exit_builtin(t_vars *vars, char **cmd_args);
int		echo_builtin(char **cmd_args);
int		pwd_builtin(t_vars *vars, char **cmd_args);
int		export_builtin(t_vars *vars, char **cmd_args);
int		unset_builtin(t_vars *vars, char **cmd_args);
int		cd_builtin(t_vars *vars, char **cmd_args);
int		env_builtin(t_vars *vars);
int		loc_builtin(t_vars *vars);

void	init_env(t_vars *vars, char **envp);

char	*show_prompt(t_vars *vars);
void	launch_message(void);
// ------------------------------------------------------ temporaire.c
bool	does_word_match(char *str, char *hard_text);
bool	does_wordstart_match(char *str, char *hard_text);
void	ft_free_null(void **ptr);
int		openfilex(char *filepath, int o_flag);
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
char	*chevron_space_maker(char *line);
char	*pipeline_space_maker(char *line);
char	*insert_space_before_actual_pos(char *line, int *actual_position);
char	*insert_space_after_actual_pos(char *line, int *actual_position);
// ------------------------------------------------ translate_dollar.c
char	**translate_dollars_all(char **array, t_vars *vars);
char	*translate_dollar(char *str, t_vars *vars);
bool	is_char_for_dolvar_name(char c);
bool	is_vardol(char *str, int i);
int		get_end_pos_vardol(char *str, int start_pos);
char	*substitute_vardol(char *str, int *start_pos, t_vars *vars);
char	*delete_char(char *str, int *i);

// ------------------------------------------------ quote_info_utils.c
void	init_quote_info(t_quote_info *qti);
void	refresh_quote_info(t_quote_info *qti, char actual_char);
bool	is_good_number_of_realquote(t_quote_info *qti);
bool	is_inside_realquote(t_quote_info *qti);
bool	is_outside_realquote(t_quote_info *qti);
bool	is_entering_realquote(t_quote_info *qti);
bool	is_exiting_realquote(t_quote_info *qti);
bool	is_inside_single_realquote(t_quote_info *qti);

bool	is_line_with_correct_quote(char *line, t_vars *vars);
// -------------------------------------------------------------------

// -------------------------------------------------------------------
bool	is_grammar_correct(char *line, t_vars *vars);
bool	is_grammar_chevron_correct(char *line, t_vars *vars);
bool	is_grammar_pipeline_correct(char *line, t_vars *vars);
// ------------------------------------------- chevron_segment_utils.c
int		get_segment_fd_in(t_vars *vars, char **array);
int		get_segment_fd_out(char **array);
void	clear_chevron_segment(char **array);
// -------------------------------------------------------------------



char	*find_cmd_path(t_env *env, char *cmd);
int		run_cmd(t_vars *vars, char **cmd_args, int output);
void	exec_cmd(t_vars *vars, char **cmd_args);

void	here_doc(char *limiter);

void	err_msg(char *msg);
void	exit_msg(char *msg);
int		manage_perror(char *remark, int error_code); 

void	clean_program(t_vars *vars);


void	stop_echoctl(void);
void	start_echoctl(void);
// -------------------------------------------------------------------
#endif
