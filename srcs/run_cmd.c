/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:42:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/02 12:51:53 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd_path(t_env *env, char *cmd)
{
	char	**dirs;
	char	*cmd_path;
	char	*path;
	int		i;

	path = get_var(env, "PATH")->data;
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		cmd_path = ft_pathjoin(dirs[i], cmd);
		if (access(cmd_path, 0) == 0)
		{
			ft_free_array(dirs);
			return (cmd_path);
		}
		ft_free_null((void**)&cmd_path);
		i++;
	}
	ft_free_array(dirs);
	return (NULL);
}

void	run_cmd(t_vars *vars, char *cmd, int output)
{
	int	id;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		err_msg(ERR_PIPE);
	id = fork();
	if (id == -1)
		err_msg(ERR_FORK);
	if (id == 0)
	{	
		close(pipe_fd[0]);
		if (output)
			dup2(output, 1);
		else
			dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		exec_cmd(vars, cmd);
		exit(1);
	}
	close(pipe_fd[1]);
	if (!output)
		dup2(pipe_fd[0], 0);
	else
		dup2(vars->stdin_fd, 0);
	close(pipe_fd[0]);
	waitpid(id, NULL, 0);
}

void	exec_cmd(t_vars *vars, char *cmd)
{
	char	**cmd_args;
	char	*tmp;

	cmd_args = ft_split(cmd, ' ');
	if (*cmd_args[0] != '/' && *cmd_args[0] != '.' && *cmd_args[0] != '~')
	{
		tmp = cmd_args[0];
		cmd_args[0] = find_cmd_path(vars->env, cmd_args[0]);	
		ft_free_null((void**)&tmp);
	}
	if (!cmd_args[0])
	{
		ft_free_array(cmd_args);
		err_msg(ERR_CMD);
		return ;
	}
	execve(cmd_args[0], cmd_args, NULL);
	ft_free_array(cmd_args);
	err_msg(ERR_EXECVE);
}
