/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 09:08:42 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	g_vars;

int	main(int argc, char **argv, char **envp)
{
	char	**segments;
	int		return_code;

	return_code = 0;

	if (argc > 1 || argv[1])
		exit_msg(ERR_ARGS);
	initialisation (&g_vars, envp);
	while (1)
	{
		stop_echoctl();
		g_vars.new_line = show_prompt(&g_vars);
		start_echoctl();
		if (g_vars.new_line && *(g_vars.new_line))
		{
			add_history(g_vars.new_line);
			segments = lexing(&g_vars, g_vars.new_line);
			if (segments)
				handle_segments(&g_vars, segments);
		}
		if (g_vars.new_line == NULL)
		{
			return_code = 1;
			break ;
		}
		ft_free_null((void **)&g_vars.new_line);
	}
	clean_program(&g_vars);
	
	while(1) 
	{
		sleep(1);
	}

	
	return (return_code);
}
