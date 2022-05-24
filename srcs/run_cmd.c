/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:42:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/24 14:02:48 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_child_returned_code(int status);

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

int	run_cmd(t_vars *vars, char **cmd_args, int output)
{
	int	id;
	int	pipe_fd[2];
	int	status;

	id = 0;
	if (pipe(pipe_fd) == -1)
		err_msg(ERR_PIPE);
	if (cmd_args[0])
	{
		id = fork();
		if (id == -1)
			err_msg(ERR_FORK);
		if (id == 0)
		{	
			init_signal_fork_child(&vars->sig); //ski
			close(pipe_fd[0]);
			if (!output)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
		
			if (is_builtin(cmd_args[0]))
				exit(exec_builtin(vars, cmd_args));
			else
				exec_cmd(vars, cmd_args);
		}
	}
	init_signal_fork_parent(&vars->sig); //ski
	close(pipe_fd[1]);
//	if (!output)
		dup2(pipe_fd[0], 0);
//	else
//		dup2(vars->stdin_fd, 0);
	close(pipe_fd[0]);
	if (waitpid(id, &status, 0) == -1)
		return -1;		

	return (get_child_returned_code(status));
}

void	exec_cmd(t_vars *vars, char **cmd_args)
{
	char	*tmp;
	char	**char_array;

	if (*cmd_args[0] != '/' && *cmd_args[0] != '.' && *cmd_args[0] != '~')
	{
		tmp = cmd_args[0];
		cmd_args[0] = find_cmd_path(vars->env, cmd_args[0]);	
		ft_free_null((void**)&tmp);
	}
	if (!cmd_args[0] || (access(cmd_args[0], 0) != 0))
	{
		err_msg(ERR_CMD);
		exit(127);
	}
	char_array = conv_list_to_array(vars->env);
	execve(cmd_args[0], cmd_args, char_array);
	err_msg(ERR_EXECVE);
	ft_free_array(char_array);
	exit(1);
}

/* ************************************************************************** */
static int get_child_returned_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_printf("Quit: 3\n");
		return (128 + WTERMSIG(status));
	}
	return (1);
}

/* ************************************************************************** */
// Pour connaître la RAISON du changement d’état du CHILD depuis la PARENT, 
// il faut utiliser les les MACRO suivantes avec la variable stat_loc:
// if(WIFEXITED(stat_loc))	→ fin normale
// if(WIFSIGNALED(stat_loc))	→ SIGNAL POSIX
// if(WIFSTOPPED(stat_loc))	→ CHILD en pause ou suspendu
	
// En fonction du type de fin du CHILD, 
//on peut récupérer des informations, avec les MACRO suivante:

// WEXITSTATUS(stat_loc)		→ valeur retourné par CHILD
// WTERMSIG(stat_loc)		→ numéro du SIGNAL reçu par CHILD
// WCOREDUMP(stat_loc)		→ à clarifier
// WSTOPSIG(stat_loc)		→ à clarifier 
