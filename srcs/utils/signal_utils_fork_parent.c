/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_fork_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/19 17:53:07 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	init_struct_sa_fork_parent(t_sig *s);
static void	init_sigaction_fork_parent(t_sig *s);

/* ************************************************************************** */
void	init_signal_fork_parent(t_sig *s)
{
	init_struct_sa_fork_parent(s);
	init_sigaction_fork_parent(s);
}

/* ************************************************************************** */
static void	init_struct_sa_fork_parent(t_sig *s)
{
	// SIGINT -----------------------------------------	
	s->sa_sigint.sa_handler = &handler_signal_fork_parent;
	s->sa_sigint.sa_flags = SA_RESTART;
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit.sa_handler = SIG_IGN;
}

/* ************************************************************************** */
static void	init_sigaction_fork_parent(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);
}

/* ************************************************************************** */
void	handler_signal_fork_parent(int sig_code)
{
	if (sig_code == SIGINT)
	{	
		write(1, "\n", 1);
	}
}

/* ************************************************************************** */
