/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:10:05 by gudias            #+#    #+#             */
/*   Updated: 2022/05/16 13:51:19 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// [gudias] @ minishell>
// gudias ~/Projects/minishell>

static char	*get_prompt_line(t_env *env)
{
	char	*prompt_line;
	char	*user;
	char	*dir;
	char	*home;
	char	*tmp;

	//getcwd(dir, CWD_BUF_SIZE) != NULL)
	if (does_var_exist(env, "USER") && does_var_exist(env, "PWD") && does_var_exist(env, "HOME"))
	{
		user = get_var(env, "USER")->data;
		dir = get_var(env, "PWD")->data;
		home = get_var(env, "HOME")->data;

		if (!ft_strncmp(dir, home, ft_strlen(home)))
		{
			prompt_line = ft_substr(dir, ft_strlen(home), ft_strlen(dir) - ft_strlen(home));
			//prompt_line = ft_strjoin("~/", user);
			tmp = prompt_line;
			prompt_line = ft_strjoin(CYAN"~", prompt_line);
			free(tmp);
		}
		else
			prompt_line = ft_strjoin(CYAN, dir);

		tmp = prompt_line;
		prompt_line = ft_strjoin(prompt_line, " > "DEFAULT);
		free(tmp);
	}
	else
		prompt_line = ft_strdup("minishell> ");	

	return (prompt_line);
}

char	*show_prompt(t_vars *vars)
{
	char	*prompt_line;
	char	*new_line;
	
	prompt_line = get_prompt_line(vars->env);
	new_line = readline(prompt_line);
	
	free(prompt_line);
	return (new_line);
}

void	launch_message()
{
	ft_putstr(BLUE"\n#################################################################\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_printf("#\t\t\t%s| %sHELLO %sMINI %sSHELL %s|%s\t\t\t#\n", CYAN, RED, YELLOW, GREEN, CYAN, BLUE);
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#\t\t\t\t\t\t\t\t#\n");
	ft_putstr("#################################################################\n\n"DEFAULT);
}
