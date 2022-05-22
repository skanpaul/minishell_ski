/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 00:59:19 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_return_code(t_vars *vars, int return_code)
{
	char	*buff;

	buff = 	ft_itoa(return_code);
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
	
	//reset
	vars->segments_count = 0;	
	ft_free_array(segments);					
}

int	check_assignations(t_vars *vars, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[i] && is_assignation(cmd->args[i]))
	{
		while (cmd->args[++i])
		{
			if (!is_assignation(cmd->args[i]))
				break ;
		}
		if (!(cmd->args[i]) && vars->segments_count == 1)
		{
			translate_dollars_all(cmd->args, vars);	
			add_local_var(vars, cmd->args);
		}
	
		//refresh cmd->args ? or return i ...
	}
	return (i);
}

void	parse_line(t_vars *vars, char *line, int output)
{
	t_cmd		cmd;
	int		i;
	int		return_code;
   
	return_code = 0;
	
	cmd.args = split_shell_line(line, ' ');
	if (!(cmd.args) || !(cmd.args[0]))
		return ; 
	
	//get redirs
	get_redirections(vars, &cmd);

	//exec redirs
	if (cmd.fd_in)
		dup2(cmd.fd_in, 0);
	if (cmd.fd_out)
		dup2(cmd.fd_out, 1);
	else
		cmd.fd_out = output;

	//check assignation
	//i = check_assigations(vars, &cmd);
	i = 0;
	if (cmd.args[i] && is_assignation(cmd.args[i]))
	{
		while (cmd.args[++i])
		{
			if (!is_assignation(cmd.args[i]))
				break ;
		}

		translate_dollars_all(cmd.args, vars);
		if (!(cmd.args[i]) && vars->segments_count == 1)
			return_code = add_local_var(vars, cmd.args);
	}

	//execute cmds
	translate_dollars_all(cmd.args, vars);
	if (cmd.args[i] && vars->segments_count == 1 && is_builtin(cmd.args[i]))
		return_code = exec_builtin(vars, (cmd.args) + i);
	else
		return_code = run_cmd(vars, (cmd.args) + i, cmd.fd_out);
	
	update_return_code();

	//resets
	init_signal_main(&vars->sig);
	//reset redirs and close fds
	if (cmd.fd_in)
	{
		close (cmd.fd_in);
	}
	if (cmd.fd_out > 1)
	{
		dup2(vars->stdout_fd, 1);
		close (cmd.fd_out);
	}
	if (output)
		dup2(vars->stdin_fd, 0);


	ft_free_array(cmd.args); // mettre cmd_args == NULL ?

}
