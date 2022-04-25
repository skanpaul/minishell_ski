/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:48:48 by gudias            #+#    #+#             */
/*   Updated: 2022/04/25 16:43:11 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
/* ************************************************************************** */
# define ERR_PIPE   "Error: pipe"
# define ERR_FORK   "Error: fork"
# define ERR_EXECVE "Error: execve"
# define ERR_MALLOC "Error: malloc"
# define ERR_CMD    "Error: command not found"
# define ERR_ARGS   "Error: bad arguments"
# define ERR_TTY    "Error: not tty"


/* ************************************************************************** */
#define PWD_NO_ERROR	0
#define PWD_ERROR		-1
// -------------------------------
#define CD_NO_ERROR		    0
#define CD_ERROR		    -1
#define CHDIR_NO_ERROR	    0
#define CHDIR_ERROR		    -1
#define CWD_BUF_SIZE    	4096
// -------------------------------

/* ************************************************************************** */
#endif
