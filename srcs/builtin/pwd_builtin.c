/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ski               #+#    #+#             */
/*   Updated: 2022/04/27 09:58:57 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
int pwd_builtin(t_vars *vars)
{
	char	cwd_name[CWD_BUF_SIZE];
	
	if (getcwd(cwd_name, CWD_BUF_SIZE) == NULL)	
		return (manage_perror("pwd_builtin", vars));
	else
	{
		write(1, cwd_name, ft_strlen(cwd_name));
		write(1, "\n", 1);
	}
	
	return (BUILTIN_SUCCESS);
}

/* ************************************************************************** */