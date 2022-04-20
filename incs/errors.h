/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sorakann <sorakann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:48:48 by gudias            #+#    #+#             */
/*   Updated: 2022/04/20 21:32:57 by sorakann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
/* ************************************************************************** */
# define ERR_PIPE   "Error: pipe"
# define ERR_FORK   "Error: fork"
# define ERR_EXECVE "Error: execve"
# define ERR_CMD    "Error: command not found"
# define ERR_ARGS   "Error: bad arguments"
# define ERR_TTY    "Error: not tty"

/* ************************************************************************** */
#define CD_NO_ERROR		    0
#define CD_ERROR		    -1
#define CD_MSG_ERR_NO_ARG	"cd: need a relative or absolut path"
#define CHDIR_NO_ERROR	    0
#define CHDIR_ERROR		    -1
// -------------------------------

/* ************************************************************************** */
#endif
