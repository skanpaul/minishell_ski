/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:44:10 by gudias            #+#    #+#             */
/*   Updated: 2022/04/27 10:19:19 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	exit_msg(char *msg)
{
	err_msg(msg);
	exit(0);
}

int manage_perror(char *remark, t_vars *vars)
{
	perror(remark);
	printf("\n");
	write_exit_failure(vars);
	return (BUILTIN_FAILURE);
}

void err_quit(int n) 
// A EFFACER: est utilise dans here_doc.c, mais ou est la definition ?
{
	(void)n;
	return ;
}