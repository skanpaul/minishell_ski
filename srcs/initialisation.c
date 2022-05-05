/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 09:17:34 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 10:09:18 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	init_vars(t_vars *vars, char **envp)
{
	(void)envp;
	vars->stdin_fd = dup(0);
	vars->stdout_fd = dup(1);
	vars->stderr_fd = dup(2);
	vars->env = NULL;
	vars->loc = NULL;
	vars->env_char_array = NULL;

}

/* ************************************************************************** */
void initialisation(t_vars *vars, char **envp)
{
	init_vars(vars, envp);
	
	init_env(vars, envp);
	
	init_sa_struc_main(&vars->sig);
	init_sigaction_main(&vars->sig);
	init_loc(vars);	
}

/* ************************************************************************** */