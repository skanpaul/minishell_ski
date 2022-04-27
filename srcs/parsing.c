/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2022/04/27 20:25:27 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_line(t_vars *vars, char *line)
{
	char	**cmd_args;
	
	//check single quotes

	//check double quotes
	
	//check redirs

	//replace $value

	cmd_args = ft_split(line, ' ');
	if (!cmd_args[0])
		return ;
	add_history(line);
	//if ("name=value" && pas de cmd) 
	// !!! si cmd ->ignore
	
	if (is_builtin(cmd_args[0]))
		exec_builtin(vars, cmd_args);
	else
		run_cmd(vars, line, 1);  //modif line ---> cmd_args (changer parsing dans exec_cmd)

	//update '$?' ici ?? (besoin de valeur de retour d'exec)
	//pourquoi?
	//$? est une variable du shell, elle se met a jour apres l'execution de qqch
	//peu importe quoi
	//un programme lancer ne doit pas gerer les var de notre shell mais retourne just 
	//son exit status: exit(0); exit(1); return(-1); etc...
	//il faut recuperer cette valeur peu importe ce qu'on a fait et mettre a jour apres
	// (ca me semble plus coherent)
	// !! modifier fonction pour qu'elle retourne le code erreur
	
	ft_free_array(cmd_args);
}
