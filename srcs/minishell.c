/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/04/13 18:23:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	FD_STDIN;

int	main(int argc, char **argv, char **envp)
{

	if (argc > 1)
		exit_msg(ERR_ARGS);
	

	FD_STDIN = dup(0);

	char *new_line;
	ft_putendl("HELLO MINISHELL");
	//------------------------------------
	while(1)
	{
		new_line = readline("minishell> ");
		if (new_line)
		{
			add_history(new_line);
			run_cmd("ls", envp, 0);
			run_cmd("grep ann", envp, 0);
			run_cmd("wc -l", envp, 1);
		}
		new_line = NULL;
		free(new_line);
	}	
	//------------------------------------
	
	return (0);
}
