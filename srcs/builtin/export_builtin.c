/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:48:59 by gudias            #+#    #+#             */
/*   Updated: 2022/05/26 18:31:53 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_smallest(t_env *env, t_env *last_small)
{
	t_env	*ptr;
	t_env	*smallest;

	ptr = env;
	while (last_small && ptr
		&& (ft_strncmp(ptr->name, last_small->name,
				ft_strlen(ptr->name) + 1) <= 0))
		ptr = ptr->next;
	smallest = ptr;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, smallest->name, ft_strlen(ptr->name) + 1) < 0)
		{
			if (!last_small || (last_small && (ft_strncmp(ptr->name,
							last_small->name, ft_strlen(ptr->name) + 1) > 0)))
				smallest = ptr;
		}
		ptr = ptr->next;
	}
	return (smallest);
}

static t_env	*sort_env_lst(t_env *env)
{	
	t_env	*sorted_env;
	t_env	*smallest;
	int		size;

	sorted_env = NULL;
	smallest = NULL;
	size = size_var_list(env);
	while (size--)
	{
		smallest = get_smallest(env, smallest);
		add_var(&sorted_env, smallest->name, smallest->data);
	}
	return (sorted_env);
}

static int	export_print(t_env *env)
{
	t_env	*tmp;
	t_env	*ptr;

	tmp = sort_env_lst(env);
	ptr = tmp;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->data)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->data, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	free_var_list(&ptr);
	return (0);
}

static	t_env	*get_name_and_data(t_vars *vars, char *arg)
{
	t_env	*var;
	char	*equal;

	var = malloc(sizeof (t_env));
	if (!var)
		return (NULL);
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		var->name = ft_substr(arg, 0, equal - arg);
		var->data = ft_substr(equal, 1, ft_strlen(equal + 1));
	}
	else
	{
		var->name = ft_strdup(arg);
		if (does_var_exist(vars->loc, var->name))
			var->data = ft_strdup(get_var(vars->loc, var->name)->data);
		else
			var->data = NULL;
	}
	var->next = NULL;
	return (var);
}

int	export_builtin(t_vars *vars, char **cmd_args)
{
	t_env	*var;
	int		i;

	if (!cmd_args[1])
		return (export_print(vars->env));
	i = 1;
	while (cmd_args[i])
	{
		var = get_name_and_data(vars, cmd_args[i]);
		if (!name_is_valid(var->name))
		{
			err_msg(ERR_EXPORT_ID);
			return (1);
		}
		else
			update_var(&vars->env, var->name, var->data);
		if (does_var_exist(vars->loc, var->name))
			update_var(&vars->loc, var->name, var->data);
		ft_free_null(&(var->data));
		ft_free_null(&(var->name));
		ft_free_null((char **)&var);
		i++;
	}
	return (0);
}
