/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:41 by gudias            #+#    #+#             */
/*   Updated: 2022/05/04 17:36:26 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export",
								"unset", "env", "exit", "loc", NULL};

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
int	exec_builtin(t_vars *vars, char **cmd_args)
{
	int	res;

	if (!ft_strncmp(cmd_args[0], "echo", 4)) // Faut-il le [+1] ou pas?
			res = echo_builtin(cmd_args);				
	else if (!ft_strncmp(cmd_args[0], "cd", 2))	 // Faut-il le [+1] ou pas?
			res = cd_builtin(vars, cmd_args); 
	else if (!ft_strncmp(cmd_args[0], "pwd", 3)) // Faut-il le [+1] ou pas?
			res = pwd_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "export", 6)) // Faut-il le [+1] ou pas?
			res = export_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "unset", 5)) // Faut-il le [+1] ou pas?
			res = unset_builtin(vars, cmd_args);
	else if (!ft_strncmp(cmd_args[0], "env", 3)) // Faut-il le [+1] ou pas?
			res = env_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "exit", 4)) // Faut-il le [+1] ou pas?
			exit_builtin(vars);
	else if (!ft_strncmp(cmd_args[0], "loc", 3)) // Faut-il le [+1] ou pas?
			res = loc_builtin(vars);
}

int	is_assignation(char *cmd)
{
	char	*equal;

	equal = ft_strchr(cmd, '=');
	if (equal && equal - cmd > 0) //check name_is_valid ici?
		return (1);
	return (0);
}

int	add_local_var(t_vars *vars, char **cmd_args)
{
	char	*name;
	char	*equal;
	char	*data;
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (equal && equal - cmd_args[i] > 0)
		{
			name = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);
			data = ft_substr(equal, 1, ft_strlen(equal + 1));
			update_var(&vars->loc, name, data);
			if (does_var_exist(vars->env, name))
					update_var(&vars->env, name, data);
			free(name);
			free(data);
		}
		i++;
	}
	return (0);
}
