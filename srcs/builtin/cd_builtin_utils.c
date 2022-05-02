/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:31:31 by ski               #+#    #+#             */
/*   Updated: 2022/05/02 14:17:17 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
char *manage_tild(char *pathname, t_vars *vars)
{
	int len;
	char *buff1;
	char *buff2;
	
	buff1 = NULL;
	buff2 = NULL;

	len = 0;	
	if (pathname[0] == '~')
	{
		buff1 = get_var(vars->env, "HOME")->data;
		len = ft_strlen(pathname);
		buff2 = ft_substr(pathname, 1, len - 1);
		ft_free_null((void**)&pathname);
		pathname = ft_strjoin(buff1, buff2);
		ft_free_null((void**)&buff2);		
	}
	return (pathname);	
}

/* ************************************************************************** */
// ATTENTION: il faut donner un PATH ABSOLUE
/* ************************************************************************** */
bool is_good_path(char *pathname, t_vars *vars)
{
	DIR	*folder;
	
	folder = opendir(pathname);
	if (folder == NULL)
		return (false);	
	closedir(folder);	
	return (true);	
}

/* ************************************************************************** */
// void print_pwd_and_oldpwd(t_vars *vars)
// {
// 	ft_printf("PWD   : [ %s ]\n", get_var(vars->env, "PWD")->data);
// 	ft_printf("OLDPWD: [ %s ]\n", get_var(vars->env, "OLDPWD")->data);	
// }
// ft_printf("\nAVANT ****************************\n");
// print_pwd_and_oldpwd(vars);
// cd_builtin(cmd_args[1], vars); //add error if cmd_args[2]
// ft_printf("\nAPRES =============================\n");
// print_pwd_and_oldpwd(vars);
// ft_printf("\n");