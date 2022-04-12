/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/04/12 18:40:16 by gudias           ###   ########.fr       */
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
		new_line = readline("minishell>");
		if (new_line)
		{
			add_history(new_line);
			lexer(new_line);
		}

		free(new_line);
	}	
	//------------------------------------
	
	return (0);
}
