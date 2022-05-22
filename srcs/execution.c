/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:29:38 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 00:35:54 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_cmd(t_vars *vars, t_cmd *cmd)
{
	
	//exec cmds
	translate_dollars_all(cmd->args, vars);
	//.
}
