/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2022/04/18 18:30:36 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <termios.h>

struct termios saved;

void restore(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}

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
	if (!isatty(0) || !isatty(1) || !isatty(2))
		exit_msg(ERR_TTY);	
	init_vars(&vars);
	init_sa_struc_main(&d);
	init_sigaction_main(&d);

	struct termios attributes;
	tcgetattr(STDIN_FILENO, &saved);
	atexit(restore);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	
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
