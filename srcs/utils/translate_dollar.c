/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:22:02 by ski               #+#    #+#             */
/*   Updated: 2022/05/05 14:57:36 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void translate_dollar_1_token(char **token, t_vars *vars)
{
	int i;
	t_quote_info qti;

	init_quote_info(&qti);
	
	i = 0;
	while ((*token)[i] != 0)
	{
		refresh_quote_info(&qti, (*token)[i]);



		(void)vars;
		// code manquant
		
		
		
		i++;
	}

}

/* ************************************************************************** */
// char *translate_dollar_1_token(char *token, t_vars *vars)
// {
// 	token = replace_vars(vars, token);	
// 	return (token);
// }

/* ************************************************************************** */
void translate_dollar_all_token(char **token_array, t_vars *vars)
{
	int i;

	i = 0;
	while (token_array[i] != NULL)
	{
		
		
		
		// translate_dollar_1_token(&token_array[i], vars);

		token_array[i] = replace_vars(vars, token_array[i]);



		
		i++;	
	}	
}

/* ************************************************************************** */
bool is_dollar_variable(char *ptr_dollar)
{
	if (ptr_dollar[1] != ' ' || ptr_dollar[1] != '\'' || ptr_dollar[1] != '\"')
		return (false);
	return (true);
}