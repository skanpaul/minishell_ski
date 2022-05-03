/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:40:32 by gudias            #+#    #+#             */
/*   Updated: 2022/05/03 15:41:03 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_vars(t_vars *vars, char *line)
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
