/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:17:34 by ski               #+#    #+#             */
/*   Updated: 2022/05/18 15:25:02 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	init_vars(t_vars *vars, char **envp);
static void	init_loc(t_vars *vars);

/* ************************************************************************** */
void initialisation(t_vars *vars, char **envp)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
		exit_msg(ERR_TTY);
	init_vars(vars, envp);
	init_env(vars, envp);
	init_signal_main(&vars->sig);
	init_loc(vars);
	launch_message();
}

/* ************************************************************************** */
static void init_vars(t_vars *vars, char **envp)
{
	(void)envp;
	vars->stdin_fd = dup(0);
	vars->stdout_fd = dup(1);
	vars->stderr_fd = dup(2);
	vars->env = NULL;
	vars->loc = NULL;
	vars->env_char_array = NULL;
	vars->segments_count = 0;
}

/* ************************************************************************** */
static void init_loc(t_vars *vars)
{
	update_var(&vars->loc, "?", EXIT_SUCCESS_STR);
}

/* ************************************************************************** */
