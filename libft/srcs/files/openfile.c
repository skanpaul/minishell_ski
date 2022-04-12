/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:56:48 by gudias            #+#    #+#             */
/*   Updated: 2022/03/23 18:08:56 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<fcntl.h>

int	openfile(char *filepath, int o_flag)
{
	int	fd;

	if (!o_flag)
		fd = open(filepath, O_RDONLY);
	else
		fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	return (fd);
}
