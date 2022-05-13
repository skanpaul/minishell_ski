/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_fork_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/13 13:49:10 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void init_struct_sa_fork_parent(t_sig *s);
static void init_sigaction_fork_parent(t_sig *s);
/* ************************************************************************** */
void init_signal_fork_parent(t_sig *s)
{
	init_struct_sa_fork_parent(s);
	init_sigaction_fork_parent(s);	
}

/* ************************************************************************** */
static void init_struct_sa_fork_parent(t_sig *s)
{
	// SIGINT -----------------------------------------	
	s->sa_sigint.sa_handler = &handler_signal_fork_parent;	// SA_HANDLER	
	sigemptyset(&s->sa_sigint.sa_mask);				// SA_MASK
	sigaddset(&s->sa_sigint.sa_mask, SIGINT);			// -
	sigaddset(&s->sa_sigint.sa_mask, SIGQUIT);			// -	
	s->sa_sigint.sa_flags = SA_RESTART;				// SA_FLAG
	
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit.sa_handler = SIG_IGN;
	// ------------------------------------------------
}

/* ************************************************************************** */
static void init_sigaction_fork_parent(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);		// [ctrl-C]: SIGINT
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);	// [ctrl-\]: SIGQUIT	
}

/* ************************************************************************** */
void	handler_signal_fork_parent(int sig_code)
{
	if (sig_code == SIGINT)
	{
		ft_printf(MSG_SIGINT_HEREDOC_PARENT);
		// update_var(&vars->loc, "?", 1);
	}
	
	if (sig_code == SIGQUIT)
		ft_printf(MSG_SIGQUIT_HEREDOC_PARENT);
}

/* ************************************************************************** */