/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_fork_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/19 15:10:16 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void init_struct_sa_fork_child(t_sig *s);
static void init_sigaction_fork_child(t_sig *s);
/* ************************************************************************** */
void init_signal_fork_child(t_sig *s)
{
	init_struct_sa_fork_child(s);
	init_sigaction_fork_child(s);	
}

/* ************************************************************************** */
static void init_struct_sa_fork_child(t_sig *s)
{
	// SIGINT -----------------------------------------	
	s->sa_sigint.sa_handler = SIG_DFL;		// SA_HANDLER	
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit.sa_handler = SIG_DFL;
}

/* ************************************************************************** */
static void init_sigaction_fork_child(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);		// [ctrl-C]: SIGINT
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);	// [ctrl-\]: SIGQUIT	
}

/* ************************************************************************** */
