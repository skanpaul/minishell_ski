/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/08 17:12:28 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
int pwd_builtin(t_vars *vars, char **cmd_args)
{
	char	cwd_name[CWD_BUF_SIZE];
	
	(void)cmd_args;
	if (getcwd(cwd_name, CWD_BUF_SIZE) == NULL)	
		return (manage_perror("pwd_builtin", errno));
	else
	{
		write(1, cwd_name, ft_strlen(cwd_name));
		write(1, "\n", 1);
	}
	
	return (BUILTIN_SUCCESS);
}

/* ************************************************************************** */