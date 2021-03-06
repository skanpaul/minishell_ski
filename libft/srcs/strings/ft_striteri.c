/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:21:52 by gudias            #+#    #+#             */
/*   Updated: 2021/10/27 13:18:29 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *str, char (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (str && f)
	{
		i = 0;
		while (str[i] != '\0')
		{
			f(i, str + i);
			i++;
		}
	}
}
