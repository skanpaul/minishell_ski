/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:16 by gudias            #+#    #+#             */
/*   Updated: 2022/05/18 15:49:54 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
