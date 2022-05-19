/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ski <ski@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:16 by gudias            #+#    #+#             */
/*   Updated: 2022/05/19 16:44:17 by ski              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	stop_echoctl(void)
{
	struct termios	termios_new;
	struct termios	termios_save;

	if (tcgetattr(0, &termios_save))
	{
		perror("Error: tcgetattr() failed");
		exit(1);
	}
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("Error: tcsetattr() failed");
		exit(1);
	}
}

/* ************************************************************************** */
void	start_echoctl(void)
{
	struct termios	termios_new;
	struct termios	termios_save;

	if (tcgetattr(0, &termios_save))
	{
		perror("Error: tcgetattr() failed");
		exit(1);
	}
	termios_new = termios_save;
	termios_new.c_lflag |= ECHOCTL;
	if (tcsetattr(0, 0, &termios_new))
	{
		perror("Error: tcsetattr() failed");
		exit(1);
	}
}

/* ************************************************************************** */
//struct termios saved;

/*void restore(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}*/

	//------------------------------------
	//struct termios attributes;
	//(void)attributes;
	//tcgetattr(STDIN_FILENO, &saved);
	//atexit(restore);
	//tcgetattr(STDIN_FILENO, &attributes);
	//attributes.c_lflag &= ~ ECHO;
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);	
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	//------------------------------------
