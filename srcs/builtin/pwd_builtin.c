/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/11 11:02:08 by ski              ###   ########.fr       */
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
		ft_printf("%s\n", cwd_name);
	
	return (BUILTIN_SUCCESS);
}

/* ************************************************************************** */