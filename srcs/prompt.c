/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:10:05 by gudias            #+#    #+#             */
/*   Updated: 2022/05/13 20:52:05 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ~/Projects/minishell>

char	*show_prompt(t_vars *vars)
{
	char	*user;
	char	*dir;
	char	*prompt;
	char	*new_line;
	char	*to_trim;
	
	if (does_var_exist(vars->env, "USER"))
		user = get_var(vars->env, "USER")->data;
	if (does_var_exist(vars->env, "PWD"))
		dir = get_var(vars->env, "PWD")->data;
	//getcwd(dir, CWD_BUF_SIZE) != NULL)
	
	if (!ft_strncmp(dir, "/home/", 6))
	{
		to_trim = ft_strjoin("/home/", user);
		ft_putendl(to_trim);
		ft_putendl(dir);
		prompt = ft_strtrim(dir, to_trim);
		ft_putendl(prompt);
		free(to_trim);
		prompt = ft_strjoin("~/", prompt);
	}
	else
		prompt = ft_strdup(dir);
	prompt = ft_strjoin(prompt, "> ");
	new_line = readline(prompt);
	
	free(prompt);
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
