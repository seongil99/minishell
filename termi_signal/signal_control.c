/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:19:54 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/25 15:23:29 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(void)
{
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	exit(1);
}

void signal_exec(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		printf("\n");
	}
	if (sig == SIGQUIT)
	{
		g_exit_code = 131;
		printf("Quit: 3\n");
	}
}

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
