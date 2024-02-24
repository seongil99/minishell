/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:24:06 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/24 20:05:25 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_to_next_cmd(t_cmd_lst *lst)
{
	while (lst->curr && is_cmd_for_move(lst->curr))
	{
		if (lst->curr->type == LPAR)
			exec_subshell(lst);
		else if (lst->curr->type == RPAR)
		{
			close_pipe(lst);
			waitpid(-1, &g_exit_code, 0);
			g_exit_code = WEXITSTATUS(g_exit_code);
			exit(g_exit_code);
		}
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
	if (lst->curr && !is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
}
