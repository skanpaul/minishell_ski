/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:48:48 by gudias            #+#    #+#             */
/*   Updated: 2022/05/23 15:27:37 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
/* ************************************************************************** */
# define ERR_PIPE   	"minishell: Error: pipe"
# define ERR_FORK   	"minishell: Error: fork"
# define ERR_EXECVE 	"minishell: Error: execve"
# define ERR_MALLOC 	"minishell: Error: malloc"
# define ERR_CMD    	"minishell: Error: command not found"
# define ERR_ARGS   	"minishell: Error: bad arguments"
# define ERR_TTY    	"minishell: Error: not tty"
# define ERR_EXIT_NUM	"minishell: exit: numeric argument required"
# define ERR_EXIT_ARG	"minishell: exit: too many arguments"
# define ERR_EXPORT_ID	"minishell: export: not a valid identifier"
/* ************************************************************************** */
#define BUILTIN_SUCCESS			0
#define BUILTIN_FAILURE			-1
#define BUILTIN_FAILURE_PLUS	1
// -------------------------------
#define CHDIR_NO_ERROR	    0
#define CHDIR_ERROR		    -1
#define CWD_BUF_SIZE    	4096
// -------------------------------
#define EXIT_SUCCESS_STR	"0"
#define EXIT_FAILURE_STR	"1"

/* ************************************************************************** */
#endif
