/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:20:41 by gudias            #+#    #+#             */
/*   Updated: 2022/05/06 17:51:36 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_vars *vars)
{
	//----> free all here to exit properly <----
	free_var_list(&vars->env);
  //free var_locals
  
	//free(newline) ??
  
	exit(0);
}
