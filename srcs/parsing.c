/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/05/09 14:04:04 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parse_line(t_vars *vars, char *line, int output)
{
	char	**cmd_args;
	int		i;
	int		return_code;
       
	return_code = -1;
	
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
	if (cmd_args == NULL || !cmd_args[0])
		return ;		
	translate_dollars_all(cmd_args, vars);	
	i = 0;
	if (is_assignation(cmd_args[i]))
	{
		while (cmd_args[++i])
		{
			if (!is_assignation(cmd_args[i]))
				break ;
		}
		if (!cmd_args[i])
			return_code = add_local_var(vars, cmd_args);
	}

	
	//if (cmd_args[i] && is_builtin(cmd_args[i]))
	//	return_code = exec_builtin(vars, cmd_args + i, output);
	//else
	 if (cmd_args[i])
		return_code = run_cmd(vars, cmd_args + i, output);
	
	update_var(&vars->loc, "?", ft_itoa(return_code)); //free le itoa

	ft_free_array(cmd_args);
}
