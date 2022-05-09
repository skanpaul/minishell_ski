/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:44:10 by gudias            #+#    #+#             */
/*   Updated: 2022/05/08 17:25:29 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

/* ************************************************************************** */
void	exit_msg(char *msg)
{
	err_msg(msg);
	exit(1);
}

/* ************************************************************************** */
int manage_perror(char *remark, int error_code)
{
	perror(remark);
	ft_printf("\n"); // a effacer, si besoin
	return (error_code);
}

/* ************************************************************************** */
void err_quit(int n) 
// A EFFACER: est utilise dans here_doc.c, mais ou est la definition ?
{
	(void)n;
	return ;
}
