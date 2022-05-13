/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:20:41 by gudias            #+#    #+#             */
/*   Updated: 2022/05/13 17:22:21 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_zeros(char *str)
{
	if (!str)
		return (0);
	while (*str == '0')
		str++;
	if (*str)
		return (0);
	return (1);
}

int	exit_builtin(t_vars *vars, char **cmd_args)
{
	int	exit_code;

	ft_putstr_fd("exit\n", vars->stdout_fd);
	if (!cmd_args[1])
		exit_code = 0;
	else if (!ft_isnumber(cmd_args[1]) || \
		(!is_zeros(cmd_args[1]) && ft_atoi(cmd_args[1]) == 0))
	{
		err_msg("exit: numeric argument required");
		exit_code = 2;
	}
	else if (cmd_args[2])
	{
		err_msg("exit: too many arguments");
		return (1);
	}
	else
		exit_code = ft_atoi(cmd_args[1]);
	
	//----> free all here to exit properly <----
	free_var_list(&vars->env);
  	//free var_locals
	//free(newline) ??

	exit(exit_code);
}
