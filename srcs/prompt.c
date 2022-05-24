/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:10:05 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 19:58:58 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt_line(t_env *env)
{
	char	*prompt_line;
	char	dir[CWD_BUF_SIZE];
	char	*home;
	char	*tmp;

	if (getcwd(dir, CWD_BUF_SIZE) != NULL && does_var_exist(env, "HOME"))
	{
		home = get_var(env, "HOME")->data;
		if (!ft_strncmp(dir, home, ft_strlen(home)))
		{
			prompt_line = ft_strdup(dir + ft_strlen(home));
			tmp = prompt_line;
			prompt_line = ft_strjoin(CYAN"~", prompt_line);
			free(tmp);
		}
		else
			prompt_line = ft_strjoin(CYAN, dir);
	}
	else
		prompt_line = ft_strdup(RED"minishell");
	tmp = prompt_line;
	prompt_line = ft_strjoin(prompt_line, " > "DEFAULT);
	free(tmp);
	return (prompt_line);
}

char	*show_prompt(t_vars *vars)
{
	char	*prompt_line;
	char	*new_line;

	prompt_line = get_prompt_line(vars->env);
	stop_echoctl();
	new_line = readline(prompt_line);
	start_echoctl();
	free(prompt_line);
	return (new_line);
}

void	launch_message(void)
{
	ft_putstr(BLUE"\n###############################################");
	ft_putstr("##################\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_printf("#\t\t\t%s| %sHELLO %sMINI %sSHELL %s|%s\t\t\t#\n",
		CYAN, RED, YELLOW, GREEN, CYAN, BLUE);
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#####################################################");
	ft_putstr("############\n\n"DEFAULT);
}
