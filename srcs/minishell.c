/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/04/12 17:36:59 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *new_line;
	ft_putendl("HELLO MINISHELL");


	//------------------------------------
	while(1)
	{
		new_line = readline("minisell>");
		if (new_line)
			add_history(new_line);
		printf("%s\n", new_line);
	}
	//------------------------------------
	
	return (0);
}
