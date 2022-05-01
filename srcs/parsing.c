/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/01 04:36:38 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*replace_vars(t_vars *vars, char *line)
{
	char	*dollar_ptr;
	char	*result;
	char	*var_name_end;
	char	*name;
	char	*var_value;
	char	*begin;
	char	*end;

	result = line;
	dollar_ptr = ft_strchr(line, '$');
	while (dollar_ptr)
	{
		var_value = NULL;
		begin = ft_substr(result, 0, dollar_ptr - result);
		var_name_end = ft_strchr(dollar_ptr, ' '); //should also look for $ et " ..
		if (!var_name_end)
			var_name_end = dollar_ptr + ft_strlen(dollar_ptr);
		name = ft_substr(dollar_ptr, 1, var_name_end - (dollar_ptr + 1));
		if (ft_strlen(name) > 1)
		{
			if (does_var_exist(vars->env, name))
				var_value = get_var(vars->env, name)->data;
			else if (does_var_exist(vars->loc, name))
				var_value = get_var(vars->loc, name)->data;
			if (var_value)
				begin = ft_strjoin(begin, var_value); //free
		}
		else
			begin = ft_strjoin(begin, "$"); //free
		end = ft_substr(var_name_end, 0, ft_strlen(var_name_end));
		result = ft_strjoin(begin, end);
		dollar_ptr = ft_strchr(result + ft_strlen(begin), '$');
		free(begin);
		free(name);
		free(end);
	}
	//pas oublier les free

	return (result);
}

void	parse_line(t_vars *vars, char *line)
{
	char	**cmd_args;
	int		i;
	
	//check single quotes

	//check double quotes
	
	//check redirs

	//replace $values
	line = replace_vars(vars, line);
	ft_putendl(line);
	
	
	cmd_args = ft_split(line, ' ');
	if (!cmd_args[0])
		return ;
	add_history(line);

	i = 0;
	if (is_assignation(cmd_args[i]))
	{
		while (cmd_args[++i])
		{
			if (!is_assignation(cmd_args[i]))
				break ;
		}
		if (!cmd_args[i])
			add_local_var(vars, cmd_args);
	}
	if (cmd_args[i] && is_builtin(cmd_args[i]))
		exec_builtin(vars, cmd_args + i);
	else if (cmd_args[i])
		run_cmd(vars, line, 1);  //modif line ---> cmd_args (changer parsing dans exec_cmd)

	//update '$?' ici ?? (besoin de valeur de retour d'exec)
	//pourquoi?
	//$? est une variable du shell, elle se met a jour apres l'execution de qqch
	//peu importe quoi
	//un programme lancer ne doit pas gerer les var de notre shell mais retourne just 
	//son exit status: exit(0); exit(1); return(-1); etc...
	//il faut recuperer cette valeur peu importe ce qu'on a fait et mettre a jour apres
	// (ca me semble plus coherent)
	// 	!!! -->modifier fonction pour qu'elle retourne le code erreur
	
	ft_free_array(cmd_args);
}
