/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_maker_chevron.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 06:15:33 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/23 17:18:52 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static bool	is_chevron(char c);
static bool	is_white_space(char c);
static bool	is_prev_char_correct(char *line, int actual_position);
static bool	is_next_char_correct(char *line, int actual_position);
static char	*insert_space_before_actual_pos(char *line, int *actual_position);
static char	*insert_space_after_actual_pos(char *line, int *actual_position);

/* ************************************************************************** */
char *chevron_space_maker(char *line)
{
    int i;
	t_quote_info qti;

	init_quote_info(&qti);

	i = 0;
    while (line[i] != 0)
	{
		refresh_quote_info(&qti, line[i]);
		
		if (is_chevron(line[i]) && is_outside_realquote(&qti))
		{
			if (is_prev_char_correct(line, i) == false)
				line = insert_space_before_actual_pos(line, &i);

			if (is_next_char_correct(line, i) == false)
				line = insert_space_after_actual_pos(line, &i);
		}
		i++;		
	}
    return (line);
}

/* ************************************************************************** */
static char	*insert_space_before_actual_pos(char *line, int *actual_position)
{
	char *start;
	char *start_with_space;
	char *end;
	int qty;

	qty = *actual_position;
	start = ft_substr(line, 0, qty);
	
	qty = ft_strlen(line) - *actual_position;
	end = ft_substr(line, *actual_position, qty); 

	start_with_space = ft_strjoin(start, " ");
	free(start);
	
	free(line);
	line = ft_strjoin(start_with_space, end);

	free(start_with_space);
	free(end);

	(*actual_position)++;
	return (line);
}

/* ************************************************************************** */
static char	*insert_space_after_actual_pos(char *line, int *actual_position)
{
	char *start;
	char *start_with_space;
	char *end;	
	int qty;
	
	qty = *actual_position + 1;
	start = ft_substr(line, 0, qty);

	qty = ft_strlen(line) - *actual_position;
	end = ft_substr(line, *actual_position + 1, qty); 

	start_with_space = ft_strjoin(start, " ");
	free(start);
	
	free(line);
	line = ft_strjoin(start_with_space, end);

	free(start_with_space);
	free(end);

	return (line);	
}

/* ************************************************************************** */
// Correct means: another chevron or white space
/* ************************************************************************** */
static bool	is_prev_char_correct(char *line, int actual_position)
{
	if (actual_position == 0)
		return (true);
		
	if (is_chevron(line[actual_position - 1]))
		return (true);

	if (is_white_space(line[actual_position - 1]))
		return (true);
	
	return (false);	
}

/* ************************************************************************** */
// Correct means: another chevron or white space
/* ************************************************************************** */
static bool	is_next_char_correct(char *line, int actual_position)
{
	int len;

	len = ft_strlen(line);
		
	if (actual_position == len - 1)
		return (true);
		
	if (is_chevron(line[actual_position + 1]))
		return (true);

	if (is_white_space(line[actual_position + 1]))
		return (true);
		
	return (false);	
}

/* ************************************************************************** */


/* ************************************************************************** */
static bool is_chevron(char c)
{
    if (c == '<' || c == '>')
        return (true);
    return (false);
}
/* ************************************************************************** */
static bool	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

/* ************************************************************************** */
