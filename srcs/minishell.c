/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/05/18 16:00:46 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	g_vars;

int	main(int argc, char **argv, char **envp)
{
	char	*new_line;
	char	**segments;
	int		i;

	if (argc > 1 || argv[1])
		exit_msg(ERR_ARGS);
	initialisation (&g_vars, envp);
	new_line = NULL;
	while (1)
	{
		new_line = show_prompt(&g_vars);
		if (new_line && *new_line)
		{
			add_history(new_line);
			segments = lexing(&g_vars, new_line);
			if (segments)
				handle_segments(&g_vars, segments);
		}
		ft_free_null((void **)&new_line);
	}
	clean_program(&g_vars);
	return (0);
}
