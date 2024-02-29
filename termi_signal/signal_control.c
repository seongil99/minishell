/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:19:54 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/29 19:20:48 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	exit(1);
}

void	signal_exec(int sig)
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
