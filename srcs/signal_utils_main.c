/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/04/18 14:46:17 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	handler_signal_main(int sig_code)
{
	if (sig_code == SIGINT)
	{
		//write(1, MSG_SIGINT_MAIN, ft_strlen(MSG_SIGINT_MAIN));
	}
	
	// if (sig_code == SIGQUIT)
	// {
	// 	write(1, MSG_SIGQUIT_MAIN, ft_strlen(MSG_SIGQUIT_MAIN));
	// }
}

/* ************************************************************************** */
void init_sigaction_main(t_data *d)
{
	// signal(SIGINT, handler_signal_main);	// [ctrl-C]: SIGINT
	// signal(SIGQUIT, SIG_IGN);				// [ctrl-\]: SIGQUIT
		
	sigaction(SIGINT, &d->sa_sigint_main, NULL);	// [ctrl-C]: SIGINT
	sigaction(SIGQUIT, &d->sa_sigquit_main, NULL);	// [ctrl-\]: SIGQUIT	
}

/* ************************************************************************** */
void init_sa_struc_main(t_data *d)
{
	// SIGINT -----------------------------------------	
	d->sa_sigint_main.sa_handler = &handler_signal_main;	// SA_HANDLER	
	sigemptyset(&d->sa_sigint_main.sa_mask);				// SA_MASK
	sigaddset(&d->sa_sigint_main.sa_mask, SIGINT);			// -
	sigaddset(&d->sa_sigint_main.sa_mask, SIGQUIT);			// -	
	d->sa_sigint_main.sa_flags = SA_RESTART;				// SA_FLAG
	
	// SIGQUIT -----------------------------------------	
	d->sa_sigquit_main.sa_handler = SIG_IGN;
	// d->sa_sigquit_main.sa_handler = &handler_signal_main;	// SA_HANDLER	
	sigemptyset(&d->sa_sigquit_main.sa_mask);				// SA_MASK
	sigaddset(&d->sa_sigquit_main.sa_mask, SIGINT);			// -
	sigaddset(&d->sa_sigquit_main.sa_mask, SIGQUIT);			// -	
	d->sa_sigquit_main.sa_flags = SA_RESTART;				// SA_FLAG
	// ------------------------------------------------
}

/* ************************************************************************** */