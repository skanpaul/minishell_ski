/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/11 13:08:05 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	handler_signal_main(int sig_code)
{
	if (sig_code == SIGINT)
	{
		write(1, MSG_SIGINT_MAIN, ft_strlen(MSG_SIGINT_MAIN));
		// update_var(&vars->loc, "?", 1);
	}
	
	 if (sig_code == SIGQUIT)
	 {
	 	write(1, MSG_SIGQUIT_MAIN, ft_strlen(MSG_SIGQUIT_MAIN));
	 }
}

/* ************************************************************************** */
void init_sigaction_main(t_sig *s)
{
	// signal(SIGINT, handler_signal_main);	// [ctrl-C]: SIGINT
	// signal(SIGQUIT, SIG_IGN);				// [ctrl-\]: SIGQUIT
		
	sigaction(SIGINT, &s->sa_sigint_main, NULL);	// [ctrl-C]: SIGINT
	sigaction(SIGQUIT, &s->sa_sigquit_main, NULL);	// [ctrl-\]: SIGQUIT	
}

/* ************************************************************************** */
void init_sa_struc_main(t_sig *s)
{
	// SIGINT -----------------------------------------	
	s->sa_sigint_main.sa_handler = &handler_signal_main;	// SA_HANDLER	
	sigemptyset(&s->sa_sigint_main.sa_mask);				// SA_MASK
	sigaddset(&s->sa_sigint_main.sa_mask, SIGINT);			// -
	sigaddset(&s->sa_sigint_main.sa_mask, SIGQUIT);			// -	
	s->sa_sigint_main.sa_flags = SA_RESTART;				// SA_FLAG
	
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit_main.sa_handler = SIG_IGN;
	// s->sa_sigquit_main.sa_handler = &handler_signal_main;	// SA_HANDLER	
	sigemptyset(&s->sa_sigquit_main.sa_mask);				// SA_MASK
	sigaddset(&s->sa_sigquit_main.sa_mask, SIGINT);			// -
	sigaddset(&s->sa_sigquit_main.sa_mask, SIGQUIT);			// -	
	s->sa_sigquit_main.sa_flags = SA_RESTART;				// SA_FLAG
	// ------------------------------------------------
}

/* ************************************************************************** */
