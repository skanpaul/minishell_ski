/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar_pipeline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:09:45 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/23 16:29:30 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static bool	is_token_pipeline_correct(char **array, t_vars *vars);
static bool	is_previous_token_correct(char **array, t_vars *vars);
static bool	is_next_token_correct(char **array, t_vars *vars);

/* ************************************************************************** */
// return: FALSE if grammar is not correct and 
bool	is_grammar_pipeline_correct(char *line, t_vars *vars)
{
	char	**array;

	if (!line)
		return (false);
	array = NULL;
	array = split_shell_line(line, ' ');
	translate_dollars_all(array, vars);
	if (!is_token_pipeline_correct(array, vars)
		|| !is_previous_token_correct(array, vars)
		|| !is_next_token_correct(array, vars))
		return (false);
	free_array (array);
	return (true);
}

/* ************************************************************************** */
// pipeline token like [ || , ||| , |||| , ... ] are NOT correct
// -------------------------------------------------
static bool	is_token_pipeline_correct(char **array, t_vars *vars)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (does_wordstart_match(array[i], "|"))
		{
			if (!does_word_match(array[i], "|"))
			{
				update_var(&vars->loc, "?", "258");
				ft_printf("minishell: syntax error near token ");
				ft_printf("\'%s\'\n", array[i]);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

/* ************************************************************************** */
// pipeline token [ | ] can NOT bet PRECEDED by
//		a) token starting with [ < , << , <<< , <<<< , ... ]
//		b) token starting with [ > , >> , >>> , >>>> , ... ]
// -------------------------------------------------
static bool	is_previous_token_correct(char **array, t_vars *vars)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (does_word_match(array[i], "|"))
		{
			if (i == 0
				|| does_wordstart_match(array[i - 1], "<")
				|| does_wordstart_match(array[i - 1], ">"))
			{
				update_var(&vars->loc, "?", "258");
				ft_printf("minishell: syntax error near token ");
				ft_printf("\'%s\'\n", array[i]);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

/* ************************************************************************** */
// pipeline token [ | ] can NOT be FOLLOWED by
//		a) empty token
// -------------------------------------------------
static bool	is_next_token_correct(char **array, t_vars *vars)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (does_word_match(array[i], "|"))
		{
			if (array[i + 1] == NULL
				|| array[i + 1][0] == '\0')
			{
				update_var(&vars->loc, "?", "258");
				ft_printf("minishell: syntax error near token ");
				ft_printf("\'%s\'\n", array[i]);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

/* ************************************************************************** */
// RETURN: NULL if grammar is not correct and 
// !!! WARNING: exit the main program if NULL is returned
// char	*check_grammar_pipeline(char *line, t_vars *vars)
// {
//     char	**array;
// 	if (!line)
// 		return (NULL);	
// 	array = NULL;
// 	array = split_shell_line(line, ' ');
// 	// print_array_in_line(array, "A)   tokens     :\t ");
// 	translate_dollars_all(array, vars);
// 	// print_array_in_line(array, "B)   tok. trans.:\t ");
//     if (!is_token_pipeline_correct(array, vars)
// 		|| !is_previous_token_correct(array, vars)
// 		|| !is_next_token_correct(array, vars))
// 		ft_free_null((void **)&line);    
//     free_array(&array);
//     return (line);
// }
/* ************************************************************************** */