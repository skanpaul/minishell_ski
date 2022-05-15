/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:18:13 by ski               #+#    #+#             */
/*   Updated: 2022/05/15 23:37:12 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
bool does_word_match(char *str, char *hard_text)
{
	int res;

	res = ft_strncmp(str, hard_text, ft_strlen(hard_text) + 1);
	if (res == 0)
		return (true);
	return (false);	
}

/* ************************************************************************** */
bool does_wordstart_match(char *str, char *hard_text)
{
	int res;

	res = ft_strncmp(str, hard_text, ft_strlen(hard_text));
	if (res == 0)
		return (true);
	return (false);	
}
/* ************************************************************************** */
void ft_free_null(void **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

/* ************************************************************************** */
void ft_add_history(char *new_line)
{
	if (new_line[0] != '\0' || new_line != NULL)
		add_history(new_line);
}

/* ************************************************************************** */
int	openfilex(char *filepath, int o_flag)
{
	int	fd;

	fd = -1;
	if (o_flag == 0)
		fd = open(filepath, O_RDONLY);
	else if (o_flag == 1)
		fd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (o_flag == 2)
		fd = open(filepath, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

/* ************************************************************************** */
void restore_config(t_vars *vars)
{
	init_signal_main(&vars->sig); //ski
	if(does_var_exist(vars->env, "PWD"))
		chdir(get_var(vars->env, "PWD")->data);
}

/* ************************************************************************** */
int get_child_returned_code(int status)
{
	if (WIFEXITED(status))
	{
		ft_printf("WIFEXITED\n");
		return (WEXITSTATUS(status));
	}

	if (WIFSIGNALED(status))
	{
		ft_printf("WIFSIGNALED\n");		
		return (128 + WTERMSIG(status));	
	}

	// A CLARIFIER ENCORE SELON LES POSSIBILITE CI DESSOUS
	return (0);
}

/* ************************************************************************** */

// Pour connaître la RAISON du changement d’état du CHILD depuis la PARENT, 
// il faut utiliser les les MACRO suivantes avec la variable stat_loc:
// if(WIFEXITED(stat_loc))	→ fin normale
// if(WIFSIGNALED(stat_loc))	→ SIGNAL POSIX
// if(WIFSTOPPED(stat_loc))	→ CHILD en pause ou suspendu
	
// En fonction du type de fin du CHILD, 
//on peut récupérer des informations, avec les MACRO suivante:

// WEXITSTATUS(stat_loc)		→ valeur retourné par CHILD
// WTERMSIG(stat_loc)		→ numéro du SIGNAL reçu par CHILD
// WCOREDUMP(stat_loc)		→ à clarifier
// WSTOPSIG(stat_loc)		→ à clarifier 