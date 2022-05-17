/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/17 14:47:34 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*sort_env_lst(t_env *env)
{	
	t_env	*sorted_env;
	t_env	*ptr;
	t_env	*smallest;
	char	*last;
	int		i;
	int		size;

	last = "\0";
	sorted_env = NULL;
	size = size_var_list(env);
	i = 0;
	while (i < size)
	{
		ptr = env;
		while (ptr && ft_strncmp(ptr->name, last, ft_strlen(ptr->name) + 1) < 0 )
			ptr = ptr->next;
		smallest = ptr;
		while (ptr)
		{
			if ((ft_strncmp(ptr->name, smallest->name, ft_strlen(ptr->name) + 1) < 0) &&
					(ft_strncmp(ptr->name, last, ft_strlen(ptr->name) + 1) > 0))
				smallest = ptr;
			ptr = ptr->next;
		}
		last = smallest->name;
		//ft_putendl(last);
		add_var(&sorted_env, smallest->name, smallest->data);
		i++;
	}
	return (sorted_env);
}

static int	export_print(t_env *env)
{
	t_env	*tmp;
	
	tmp = sort_env_lst(env);
	//print_var(tmp);
	while (tmp)
	{
		if (!tmp->data)
			return (0);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp->data, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	free_var_list(&tmp);
	return (0);
}

int	export_builtin(t_vars *vars, char **cmd_args)
{
	char	*name;
	char	*equal;
	char	*data;
	int	i;

	if (!cmd_args[1])
		return (export_print(vars->env));

	i = 1;
	while (cmd_args[i])
	{
		equal = ft_strchr(cmd_args[i], '=');
		if (equal)
		{
			name = ft_substr(cmd_args[i], 0, equal - cmd_args[i]);	
			data = ft_substr(equal, 1, ft_strlen(equal + 1));
		}
		else
		{
			name = ft_strdup(cmd_args[i]); 
			if (does_var_exist(vars->loc, name))
				data = ft_strdup(get_var(vars->loc, name)->data);
			else
				data = NULL;
		}
		if (ft_strlen(name) < 1) //check name_is_valid (char special, chiffre, etc..)
		{
			err_msg("export: not a valid identifier");
			return (1);
		}
		else
			update_var(&vars->env, name, data); 
  
		if (does_var_exist(vars->loc, name))
				update_var(&vars->loc, name, data);
    
		ft_free_null((void**)&data);
		ft_free_null((void**)&name);      
		i++;
	}
	return (0);
}	
