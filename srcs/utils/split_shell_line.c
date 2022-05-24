/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:47:09 by sorakann          #+#    #+#             */
/*   Updated: 2022/05/24 09:59:51 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
typedef struct s_ssl
{
	char			**array;
	t_quote_info	qti;
}	t_ssl;

/* ************************************************************************** */
static int	count_words(char *line, char separator);
static void	get_array(t_ssl *ssl, char *line, char sep);

/* ************************************************************************** */
char	**split_shell_line(char *line, char sep)
{
	t_ssl			ssl;

	init_quote_info(&ssl.qti);
	if (!line)
		return (NULL);
	ssl.array = malloc (sizeof (char *) * (count_words(line, sep) + 1));
	if (!ssl.array)
		return (NULL);
	get_array(&ssl, line, sep);
	return (ssl.array);
}

/* ************************************************************************** */
static void	get_array(t_ssl *ssl, char *line, char sep)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (line[i] != '\0')
	{
		refresh_quote_info(&ssl->qti, line[i]);
		if ((line[i] != sep) && (i == 0 || (line[i - 1] == sep
					&& (is_outside_realquote(&ssl->qti)
						|| is_entering_realquote(&ssl->qti)))))
			start = i;
		if ((line[i] != sep) && (line[i + 1] == '\0' || (line[i + 1] == sep
					&& (is_outside_realquote(&ssl->qti)
						|| is_exiting_realquote(&ssl->qti)))))
			ssl->array[j++] = ft_substr(line, start, (i - start) + 1);
		i++;
	}
	ssl->array[j] = 0;
}

/* ************************************************************************** */
static int	count_words(char *line, char separator)
{
	int				i;
	int				count;
	t_quote_info	qti;

	init_quote_info(&qti);
	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		refresh_quote_info(&qti, line[i]);
		if (line[i] != separator)
		{
			if (i == 0 || (line[i - 1] == separator
					&& (is_outside_realquote(&qti)
						|| is_entering_realquote(&qti))))
				count++;
		}
		i++;
	}
	return (count);
}

/* ************************************************************************** */
// char	**ft_split(char const *str, char c)
// {
// 	char	**res;
// 	int		i;
// 	int		j;
// 	int		start;

// 	if (!str)
// 		return (NULL);
// 	res = malloc (sizeof (char *) * (count_words(str, c) + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	while (str[i] != '\0')
// 	{
// 		if ((str[i] != c) && (i == 0 || (str[i - 1] == c)))
// 			start = i;
// 		if ((str[i] != c) && ((str[i + 1] == '\0') || (str[i + 1] == c)))
// 			res[j++] = ft_substr(str, start, (i - start) + 1);
// 		i++;
// 	}
// 	res[j] = 0;
// 	return (res);
// }

/* ************************************************************************** */