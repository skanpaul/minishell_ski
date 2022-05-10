/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_segment_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:12:10 by ski               #+#    #+#             */
/*   Updated: 2022/05/10 17:11:14 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	delete_chevron_and_file(char **array, int *i);

/* ************************************************************************** */
void	clear_chevron_segment(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (does_word_match(array[i], "<")
			|| does_word_match(array[i], "<<")
			|| does_word_match(array[i], ">")
			|| does_word_match(array[i], ">>"))
		{
			delete_chevron_and_file(array, &i);
		}
		i++;
	}
}

/* ************************************************************************** */
static void	delete_chevron_and_file(char **array, int *i)
{
	int		j;
	char	*ptr_chevron_str;
	char	*ptr_filename;

	ptr_chevron_str = NULL;
	ptr_filename = NULL;
	ptr_chevron_str = array[*i];
	ptr_filename = array[*i + 1];
	j = 0;
	while (array[*i + j + 2])
	{
		array[*i + j] = array[*i + j + 2];
		j++;
	}
	array[*i + j] = array[*i + j + 2];
	array[*i + j + 1] = NULL;
	ft_free_null((void **)&ptr_chevron_str);
	ft_free_null((void **)&ptr_filename);
	(*i)--;
}

/* ************************************************************************** */
// RETURN -1: not possible to open a file
// RETURN  0: no file has to be open
// RETURN >2: a file was open
// NEED to close file ONLY if fd > 2
int	get_segment_fd_out(char **array)
{
	int	i;
	int	fd_out;

	fd_out = 0;
	i = 0;
	while (array[i])
	{
		if (does_word_match(array[i], ">") || does_word_match(array[i], ">>"))
		{
			if (fd_out != 0)
				close(fd_out);
			if (does_word_match(array[i], ">"))
				fd_out = open(array[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
			else
				fd_out = open(array[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (fd_out < 0)
			{
				perror(array[i + 1]);
				break ;
			}
		}
		i++;
	}
	return (fd_out);
}

/* ************************************************************************** */
// RETURN -1: not possible to open a file
// RETURN  0: no file has to be open
// RETURN >2: a file was open
// NEED to close file ONLY if fd > 2
int	get_segment_fd_in(char **array)
{
	int	i;
	int	fd_in;

	fd_in = 0;
	i = 0;
	while (array[i])
	{
		if (does_word_match(array[i], "<") || does_word_match(array[i], "<<"))
		{
			if (fd_in != 0)
				close(fd_in);
			if (does_word_match(array[i], "<"))
				fd_in = open(array[i + 1], O_RDONLY);
			else
			{
				fd_in = 56;
				ft_printf("BESOIN: heredoc [ << ] with end [ %s ]\n", array[i + 1]);
			}
			if (fd_in < 0)
			{
				perror(array[i + 1]);
				break ;
			}
		}
		i++;
	}
	return (fd_in);
}

/* ************************************************************************** */
