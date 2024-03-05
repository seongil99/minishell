/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:19:54 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/05 12:46:28 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_exit_code = 1;
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
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
}
