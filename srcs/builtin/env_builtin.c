/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:05:59 by gudias            #+#    #+#             */
/*   Updated: 2022/04/26 11:06:30 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_vars *vars, char **envp)
{
	char	*name;
	char	*data;
	int		len;
	t_env	*temp;

	while (*envp)
	{
		len = ft_strchr(*envp, '=') - *envp;
		name = ft_substr(*envp, 0, len);
		data = ft_substr(*envp, len + 1, ft_strlen(*envp));
		add_var(&vars->env, name, data);
		free(name);
		free(data);
		envp++;
	}
	//assurer que PATH, HOME, PWD, OLDPWD, SHLVL SONT PRESENTS
	//sinon -> les ajouter
	temp = get_env(vars->env, "SHLVL");
	temp->data = ft_itoa(ft_atoi(temp->data) + 1);
}

void	env_builtin(t_vars *vars)
{
	print_var(vars->env);
	// t_env	*env;

	// env = vars->env;
	// while (env)
	// {
	// 	ft_putstr_fd(env->name, 1);
	// 	ft_putstr_fd("=", 1);
	// 	ft_putstr_fd(env->data, 1);
	// 	ft_putstr_fd("\n", 1);
	// 	env = env->next;
	// }
}
