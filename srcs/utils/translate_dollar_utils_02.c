/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar_utils_02.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:22:02 by ski               #+#    #+#             */
/*   Updated: 2022/05/11 10:44:06 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
char	*delete_char(char *str, int *i)
{
	int		len;
	char	*buf_1;
	char	*buf_2;

	buf_1 = NULL;
	buf_2 = NULL;
	len = ft_strlen(str);
	buf_1 = ft_substr(str, 0, *i);
	buf_2 = ft_substr(str, *i + 1, len - *i - 1);
	ft_free_null((void **)&str);
	str = ft_strjoin(buf_1, buf_2);
	(*i)--;
	ft_free_null((void **)&buf_1);
	ft_free_null((void **)&buf_2);
	return (str);
}

/* ************************************************************************** */
int	get_end_pos_vardol(char *str, int start_pos)
{
	int	i;

	i = start_pos;
	while (is_char_for_dolvar_name(str[i + 1]))
		i++;
	return (i);
}

/* ************************************************************************** */
bool	is_char_for_dolvar_name(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

/* ************************************************************************** */
bool	is_vardol(char *str, int i)
{
	if (str[i] == '$' && is_char_for_dolvar_name(str[i + 1]))	
		return (true);
	return (false);
}

/* ************************************************************************** */
