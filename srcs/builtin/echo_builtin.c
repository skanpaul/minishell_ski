/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:05:21 by gudias            #+#    #+#             */
/*   Updated: 2022/04/19 15:49:24 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char *str, int nl)
{
	if (!str)
		return ;
	if (!nl)
		str += 3;
	ft_putstr_fd(str, 1);
	if (nl)
		write(1, "\n", 1)
