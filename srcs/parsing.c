/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 14:47:15 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_return_code(t_vars *vars, int return_code)
{
	char	*buff;

	buff = ft_itoa(return_code);
	update_var(&vars->loc, "?", buff);
	ft_free_null((void **)&buff);
}

void	handle_segments(t_vars *vars, char **segments)
{
	int	i;

	i = 0;
	while (segments[i + 1])
		parse_line(vars, segments[i++], 0);
	parse_line(vars, segments[i], 1);
	dup2(vars->stdin_fd, 0);
	vars->segments_count = 0;
	ft_free_array(segments);
}

void	parse_line(t_vars *vars, char *line, int output)
{
	t_cmd		cmd;
	int			i;
	int			return_code;

	return_code = 0;
	cmd.args = split_shell_line(line, ' ');
	if (!(cmd.args) || !(cmd.args[0]))
		return ;
	get_redirections(vars, &cmd);
	if (!cmd.fd_out)
		cmd.fd_out = output;
	i = check_assignations(vars, &cmd);
	return_code = execute_cmd(vars, &cmd, i);
	update_return_code(vars, return_code);
	init_signal_main(&vars->sig);
	reset_redirections(vars, &cmd);
	free_array(cmd.args);
}
