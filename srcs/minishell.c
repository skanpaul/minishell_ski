/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/05/25 16:05:41 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	g_vars;

int	main(int argc, char **argv, char **envp)
{
	char	**segments;

	if (argc > 1 || argv[1])
		exit_msg(ERR_ARGS);
	initialisation (&g_vars, envp);
	while (1)
	{
		g_vars.new_line = show_prompt(&g_vars);
		if (g_vars.new_line && *(g_vars.new_line))
		{
			add_history(g_vars.new_line);
			segments = lexing(&g_vars, g_vars.new_line);
			if (segments)
				handle_segments(&g_vars, segments);
		}
		if (g_vars.new_line == NULL)
		{
			clean_program(&g_vars);
			exit_msg("exit");
		}
		ft_free_null((void **)&g_vars.new_line);
	}
	clean_program(&g_vars);
	return (0);
}
