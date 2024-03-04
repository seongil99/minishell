/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:24:06 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 09:41:33 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_to_ss_end(t_cmd_lst *lst)
{
	int	num_ss;

	num_ss = 1;
	lst->curr = lst->curr->next->next;
	while (lst->curr && num_ss)
	{
		if (lst->curr->type == LPAR)
			num_ss++;
		else if (lst->curr->type == RPAR)
			num_ss--;
		lst->curr = lst->curr->next;
	}
}

void	move_to_next_cmd(t_cmd_lst *lst)
{
	while (lst->curr)
	{
		if (lst->curr->type == PIPE)
			break ;
		if ((lst->curr->type == AND_IF || \
		lst->curr->type == OR_IF) && lst->curr->next->type == LPAR)
		{
			if ((lst->curr->type == OR_IF && g_exit_code == 0) || \
			(lst->curr->type == AND_IF && g_exit_code != 0))
			{
				skip_to_ss_end(lst);
				break ;
			}
		}
		if (lst->curr->type == AND_IF || lst->curr->type == OR_IF)
			break ;
		lst->curr = lst->curr->next;
	}
	if (lst->curr)
		lst->curr = lst->curr->next;
}

pid_t	fork2(void)
{
	pid_t	id;

	id = fork();
	if (id == 1)
	{
		perror("minishell: ");
		kill(0, SIGTERM);
		exit(errno);
	}
	return (id);
}
