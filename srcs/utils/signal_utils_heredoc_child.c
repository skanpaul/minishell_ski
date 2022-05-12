/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_heredoc_child.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/13 00:16:06 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void init_struct_sa_heredoc_child(t_sig *s);
static void init_sigaction_heredoc_child(t_sig *s);
/* ************************************************************************** */
void init_signal_heredoc_child(t_sig *s)
{
	init_struct_sa_heredoc_child(s);
	init_sigaction_heredoc_child(s);	
}

/* ************************************************************************** */
static void init_struct_sa_heredoc_child(t_sig *s)
{
	// SIGINT -----------------------------------------	
	s->sa_sigint_main.sa_handler = &handler_signal_heredoc_parent;		// SA_HANDLER	
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit_main.sa_handler = SIG_IGN;
}

/* ************************************************************************** */
static void init_sigaction_heredoc_child(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint_main, NULL);	// [ctrl-C]: SIGINT
	sigaction(SIGQUIT, &s->sa_sigquit_main, NULL);	// [ctrl-\]: SIGQUIT	
}

/* ************************************************************************** */