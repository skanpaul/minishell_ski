/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar_utils_01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:22:02 by ski               #+#    #+#             */
/*   Updated: 2022/05/13 13:27:08 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
typedef struct s_sv
{
	int		end_pos;
	char	*buf_1;
	char	*buf_2;
	char	*var_data;
	char	*var_name;
	char	*str;	
}	t_sv;

/* ************************************************************************** */
static void	part_1(int *start_pos, t_vars *vars, t_sv *s);
static void	part_2(int *start_pos, t_vars *vars, t_sv *s);

/* ************************************************************************** */
void	translate_dollars_all(char **array, t_vars *vars)
{
	int	i;

	i = 0;
	if (array == NULL || array[0] == NULL)
		return ;
	while (array[i])
	{
		array[i] = translate_dollar(*(array + i), vars);
		i++;
	}	
}

/* ************************************************************************** */
char	*translate_dollar(char *str, t_vars *vars)
{
	int				i;
	t_quote_info	qti;

	(void)vars;
	init_quote_info(&qti);
	i = 0;
	while (str[i] != 0)
	{
		refresh_quote_info(&qti, str[i]);
		if (is_vardol(str, i) && !is_inside_single_realquote(&qti))
			str = substitute_vardol(str, &i, vars);
		if (is_entering_realquote(&qti) || is_exiting_realquote(&qti))
			str = delete_char(str, &i);
		i++;
	}
	return (str);
}

/* ************************************************************************** */
// [ *start_pos ] is the position of the [$] sign
char	*substitute_vardol(char *str, int *start_pos, t_vars *vars)
{
	t_sv	s;

	s.str = str;
	part_1(start_pos, vars, &s);
	part_2(start_pos, vars, &s);
	return (s.str);
}

/* ************************************************************************** */
// [ *start_pos ] is the position of the [$] sign
// [ end_pos ] is the position of the last caracters of the dollar-variable
static void	part_1(int *start_pos, t_vars *vars, t_sv *s)
{
	int	qty;
	
	(void)vars;
	qty = 0;
	s->end_pos = 0;
	s->buf_1 = NULL;
	s->buf_2 = NULL;
	s->var_name = NULL;
	s->end_pos = get_end_pos_vardol(s->str, *start_pos);
	qty = s->end_pos - *start_pos;
	s->var_name = ft_substr(s->str, *start_pos + 1, qty);
	qty = *start_pos;
	s->buf_1 = ft_substr(s->str, 0, qty);
	qty = ft_strlen(s->str) - s->end_pos - 1;
	s->buf_2 = ft_substr(s->str, s->end_pos + 1, qty);
}

/* ************************************************************************** */
static void	part_2(int *start_pos, t_vars *vars, t_sv *s)
{
	s->var_data = NULL;
	if (does_var_exist(vars->env, s->var_name))
		s->var_data = get_var(vars->env, s->var_name)->data;
	if (does_var_exist(vars->loc, s->var_name))
		s->var_data = get_var(vars->loc, s->var_name)->data;
	ft_free_null((void **)&s->str);
	if (s->var_data)
	{
		s->str = ft_strjoin(s->buf_1, s->var_data);
		ft_free_null((void **)&s->buf_1);
		s->buf_1 = s->str;
		*start_pos = *start_pos + ft_strlen(s->var_data) - 1;
	}
	else
		(*start_pos) = *start_pos - 1;
	s->str = ft_strjoin(s->buf_1, s->buf_2);
	ft_free_null((void **)&s->buf_1);
	ft_free_null((void **)&s->buf_2);
	ft_free_null((void **)&s->var_name);
}

/* ************************************************************************** */
// // [ *start_pos ] is the position of the [$] sign
// // [ end_pos ] is the position of the last caracters of the dollar-variable
// char	*substitute_vardol(char *str, int *start_pos, t_vars *vars)
// {
// 	int		end_pos;
// 	char	*buf_1;
// 	char	*buf_2;
// 	char	*var_data;
// 	char	*vardol_name;

// 	// end_pos = 0;
// 	buf_1 = NULL;
// 	buf_2 = NULL;
// 	var_data = NULL;
// 	vardol_name = NULL;
// 	end_pos = get_end_pos_vardol(str, *start_pos);
// 	vardol_name = ft_substr(str, *start_pos + 1, end_pos - *start_pos);
// 	buf_1 = ft_substr(str, 0, *start_pos);
// 	buf_2 = ft_substr(str, end_pos + 1, ft_strlen(str) - end_pos - 1);
// 	var_data = NULL;
// 	if (does_var_exist(vars->env, vardol_name))
// 		var_data = get_var(vars->env, vardol_name)->data;
// 	if (does_var_exist(vars->loc, vardol_name))
// 		var_data = get_var(vars->loc, vardol_name)->data;
// 	ft_free_null((void **)&str);
// 	if (var_data)
// 	{
// 		str = ft_strjoin(buf_1, var_data);
// 		ft_free_null((void **)&buf_1);
// 		buf_1 = str;
// 		*start_pos = *start_pos + ft_strlen(var_data) - 1;
// 	}
// 	else
// 		(*start_pos) = *start_pos - 1;
// 	str = ft_strjoin(buf_1, buf_2);
// 	ft_free_null((void **)&buf_1);
// 	ft_free_null((void **)&buf_2);
// 	ft_free_null((void **)&vardol_name);
// 	return (str);
// }

/* ************************************************************************** */
