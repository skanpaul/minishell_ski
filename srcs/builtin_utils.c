/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:41 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 16:31:40 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export",
								"unset", "env", "exit", "loc", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i]) + 1))
			return (1);
		i++;
	}
	return (0);
}

int	exec_builtin(t_vars *vars, char **cmd_args)
{
	int	res;

	if (!ft_strncmp(cmd_args[0], "echo", 5))
		res = echo_builtin(cmd_args);
	else if (!ft_strncmp(cmd_args[0], "cd", 3))
		res = cd_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "pwd", 4))
		res = pwd_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "export", 7))
		res = export_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "unset", 6))
		res = unset_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "env", 4))
		res = env_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "exit", 5))
		res = exit_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "loc", 4))
		res = loc_builtin(vars);
	return (res);
}
