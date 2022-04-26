/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:05:21 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 17:26:24 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **cmd_args)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (cmd_args[1] && !ft_strncmp(cmd_args[1], "-n", 3))
	{
		nl = 0;
		i++;
	}
	while (cmd_args[i])
	{
		if (nl && i > 1 || !nl && i > 2)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmd_args[i], 1);
		i++;
	}	
	if (nl)
		write(1, "\n", 1);
}
