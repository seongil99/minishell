/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:24:06 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/23 16:03:39 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_to_next_cmd(t_cmd_lst *lst)
{
	if (!lst->curr)
		return ;
	if (!lst->curr->next)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	while (lst->curr && is_cmd_for_move(lst->curr))
	{
		if (!ft_strncmp(lst->curr->token, "(", 2))
			exec_subshell(lst);
		else if (!ft_strncmp(lst->curr->token, ")", 2))
			exit(g_exit_code);
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
	if (lst->curr && !is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
}
