/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:17:08 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 20:05:01 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_input_mode(struct termios *org_term)
{
	tcgetattr(STDIN_FILENO, org_term);
}

void	set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void	reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}
