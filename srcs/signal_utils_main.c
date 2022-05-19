/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/19 17:51:46 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_vars	g_vars;

/* ************************************************************************** */
static void	init_struc_sa_main(t_sig *s);
static void	init_sigaction_main(t_sig *s);

/* ************************************************************************** */
void	init_signal_main(t_sig *s)
{
	init_struc_sa_main(s);
	init_sigaction_main(s);
}

/* ************************************************************************** */
static void	init_struc_sa_main(t_sig *s)
{		
	// SIGINT -----------------------------------------	
	s->sa_sigint.sa_handler = &handler_signal_main;
	s->sa_sigint.sa_flags = SA_RESTART;
	// SIGQUIT -----------------------------------------	
	s->sa_sigquit.sa_handler = SIG_IGN;
}

/* ************************************************************************** */
static void	init_sigaction_main(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);
}

/* ************************************************************************** */
void	handler_signal_main(int sig_code)
{
	if (sig_code == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		update_var(&g_vars.loc, "?", "1");
	}
}

/* ************************************************************************** */
