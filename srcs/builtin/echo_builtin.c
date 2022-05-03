/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:05:21 by gudias            #+#    #+#             */
/*   Updated: 2022/04/28 13:27:42 by ski              ###   ########.fr       */
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
		if ((nl && i > 1) || (!nl && i > 2))
		// if (nl && i > 1 || !nl && i > 2)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(cmd_args[i], 1);
		i++;
	}	
	if (nl)
		write(1, "\n", 1);
}
