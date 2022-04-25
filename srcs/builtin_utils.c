/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:41 by gudias            #+#    #+#             */
/*   Updated: 2022/04/25 19:30:47 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	int i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])))
			return (1);
		i++;
	}
	return (0);
}

void	exec_builtin(t_vars *vars, char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
			echo_builtin(cmd+5, ft_strncmp(cmd+5, "-n", 2));
	else if (!ft_strncmp(cmd, "cd", 2))
			// ski: jai besoin  du path désiré et de l-environnement du minishell
			cd_builtin(cmd+3, &vars->env);		
	else if (!ft_strncmp(cmd, "pwd", 3))
			pwd_builtin();
	else if (!ft_strncmp(cmd, "export", 6))
			(void)cmd;//export_builtin();
	else if (!ft_strncmp(cmd, "unset", 5))
			unset_builtin(vars, cmd+6);
	else if (!ft_strncmp(cmd, "env", 3))
			env_builtin(vars);
	else if (!ft_strncmp(cmd, "exit", 4))
			exit_builtin(vars);
}
