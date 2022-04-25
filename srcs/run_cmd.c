/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:42:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/25 18:08:14 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = NULL;
		i++;
	}
	free(strs);
	strs = NULL;
}

char	*find_cmd_path(t_env *env, char *cmd)
{
	char	**dirs;
	char	*cmd_path;
	char	*path;
	int		i;

	path = get_env(env, "PATH")->data;
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		cmd_path = ft_pathjoin(dirs[i], cmd);
		if (access(cmd_path, 0) == 0)
		{
			free_all(dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_all(dirs);
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
		free(tmp);
	}
	if (!cmd_args[0])
	{
		free_all(cmd_args);
		err_msg(ERR_CMD);
		return ;
	}
	execve(cmd_args[0], cmd_args, NULL);
	free_all(cmd_args);
	err_msg(ERR_EXECVE);
}
