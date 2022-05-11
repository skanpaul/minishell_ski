/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/11 11:52:01 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parse_line(t_vars *vars, char *line, int output)
{
	char	**cmd_args;
	int		i;
	int		return_code;
	int		fd_in;
	int		fd_out;
   
	return_code = -1;
	fd_in = 0;
	fd_out = 0;
	
	//check space: [ ... >file ] vs. [ ... > file ]	
	//check single quotes
	//check double quotes	
	//check redirs
	//replace $values
	
	// line = replace_vars(vars, line);
	// line = replace_vars(vars, line);
	// ft_putendl(line);		
	// cmd_args = ft_split(line, ' ');
	

	cmd_args = split_shell_line(line, ' ');
	
	if (!cmd_args || !cmd_args[0])
		return ; // Doit-on free cmd_args[0] ?
	
	translate_dollars_all(cmd_args, vars);

	//get redirs
	fd_in = get_segment_fd_in(cmd_args);
	fd_out = get_segment_fd_out(cmd_args);
	clear_chevron_segment(cmd_args);

	if (fd_in)
		dup2(fd_in, 0);
	if (fd_out)
		dup2(fd_out, 1);

	i = 0;
	if (is_assignation(cmd_args[i]))
	{
		while (cmd_args[++i])
		{
			if (!is_assignation(cmd_args[i]))
				break ;
		}
		if (!cmd_args[i] && vars->segments_count == 1)
			return_code = add_local_var(vars, cmd_args);
	}
	
	if (cmd_args[i] && vars->segments_count == 1 && is_builtin(cmd_args[i]))
		return_code = exec_builtin(vars, cmd_args + i);
	else
		return_code = run_cmd(vars, cmd_args + i, output);

	if (!cmd_args[i])
		return_code = 0;	
	update_var(&vars->loc, "?", ft_itoa(return_code)); //free le itoa

	//reset redirs and close fds
	if (fd_in)
	{
		if (output)
			dup2(vars->stdin_fd, 0);
		close (fd_in);
	}
	if (fd_out)
	{
		dup2(vars->stdout_fd, 1);
		close (fd_out);
	}
	ft_free_array(cmd_args); // mettre cmd_args == NULL ?
}
