/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/22 15:06:13 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_segments(t_vars *vars, char **segments)
{
	int	i;

	i = 0;
	while (segments[i + 1])
		parse_line(vars, segments[i++], 0);
	parse_line(vars, segments[i], 1);
	
	//reset
	vars->segments_count = 0;	
	ft_free_array(segments);					
}

void	parse_line(t_vars *vars, char *line, int output)
{
	char	**cmd_args;
	int		i;
	int		return_code;
	int		fd_in;
	int		fd_out;
	char	*buff;
   
	return_code = -1;
	fd_in = 0;
	fd_out = 0;
	
	cmd_args = split_shell_line(line, ' ');
	if (!cmd_args || !cmd_args[0])
		return ; 
	

	//get redirs
	fd_in = get_segment_fd_in(vars, cmd_args);
	fd_out = get_segment_fd_out(cmd_args);
	clear_chevron_segment(cmd_args);

	//exec redirs
	if (fd_in)
		dup2(fd_in, 0);
	if (fd_out)
		dup2(fd_out, 1);
	else
		fd_out = output;


	//check assignation
	i = 0;
	if (cmd_args[i] && is_assignation(cmd_args[i]))
	{
		while (cmd_args[++i])
		{
			if (!is_assignation(cmd_args[i]))
				break ;
		}

		translate_dollars_all(cmd_args, vars);
		if (!cmd_args[i] && vars->segments_count == 1)
			return_code = add_local_var(vars, cmd_args);
	}


	//execute cmds
	translate_dollars_all(cmd_args, vars);
	if (cmd_args[i] && vars->segments_count == 1 && is_builtin(cmd_args[i]))
		return_code = exec_builtin(vars, cmd_args + i);
	else
		return_code = run_cmd(vars, cmd_args + i, fd_out);
	

	//return code
	if (!cmd_args[i])
		return_code = 0;
	buff = 	ft_itoa(return_code);
	update_var(&vars->loc, "?", buff);
	ft_free_null((void **)&buff);

	//resets
	init_signal_main(&vars->sig);
	//reset redirs and close fds
	if (fd_in)
	{
		close (fd_in);
	}
	if (fd_out > 1)
	{
		dup2(vars->stdout_fd, 1);
		close (fd_out);
	}
	if (output)
		dup2(vars->stdin_fd, 0);


	ft_free_array(cmd_args); // mettre cmd_args == NULL ?

}
