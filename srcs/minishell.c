/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/04/18 14:22:47 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_vars(t_vars *vars)
{
	vars->stdin_fd = dup(0);
	vars->stdout_fd = dup(1);
	vars->stderr_fd = dup(2);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	d;
	t_vars	vars;
	char	*new_line;

	if (argc > 1)
		exit_msg(ERR_ARGS);

	init_vars(&vars);
	init_sa_struc_main(&d);
	init_sigaction_main(&d);
	
	ft_putendl("HELLO MINISHELL");
	//------------------------------------
	while(1)
	{
		new_line = readline("minishell> ");
		if (new_line)
		{
			add_history(new_line);
			run_cmd(&vars, new_line, envp, 1);
		}
		new_line = NULL;
		free(new_line);
	}	
	//------------------------------------
	return (0);
}
