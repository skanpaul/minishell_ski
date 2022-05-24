/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_maker_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 06:15:33 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/24 11:49:50 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static bool	is_pipeline(char c);
static bool	is_white_space(char c);
static bool	is_prev_char_correct(char *line, int actual_position);
static bool	is_next_char_correct(char *line, int actual_position);

/* ************************************************************************** */
char	*pipeline_space_maker(char *line)
{
	int				i;
	t_quote_info	qti;

	init_quote_info(&qti);
	i = 0;
	while (line[i] != 0)
	{
		refresh_quote_info(&qti, line[i]);
		if (is_pipeline(line[i]) && is_outside_realquote(&qti))
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
// Correct means: another chevron or white space
/* ************************************************************************** */
static bool	is_prev_char_correct(char *line, int actual_position)
{
	if (actual_position == 0)
		return (true);
	if (is_pipeline(line[actual_position - 1]))
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
	int	len;

	len = ft_strlen(line);
	if (actual_position == len - 1)
		return (true);
	if (is_pipeline(line[actual_position + 1]))
		return (true);
	if (is_white_space(line[actual_position + 1]))
		return (true);
	return (false);
}

/* ************************************************************************** */
static bool	is_pipeline(char c)
{
	if (c == '|')
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
