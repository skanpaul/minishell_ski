/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:41 by gudias            #+#    #+#             */
/*   Updated: 2022/05/02 11:25:51 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", "loc", NULL};

	int i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
void	exec_builtin(t_vars *vars, char **cmd_args)
{
	if (!ft_strncmp(cmd_args[0], "echo", 4))
			echo_builtin(cmd_args);		
				
	else if (!ft_strncmp(cmd_args[0], "cd", 2))
			// cd_builtin(cmd_args[1], vars); //add error if cmd_args[2]		
			cd_builtin(vars, cmd_args); 
							
	else if (!ft_strncmp(cmd_args[0], "pwd", 3))
			pwd_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "export", 6))
			export_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "unset", 5))
			unset_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "env", 3))
			env_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "exit", 4))
			exit_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "loc", 3))
			loc_builtin(vars);
}

