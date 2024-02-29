/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:24:06 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/29 22:13:22 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_to_next_cmd(t_cmd_lst *lst)
{
	while (lst->curr)
	{
		if (lst->curr->type == RPAR)
			break ;
		else if (lst->curr->type == PIPE || \
		lst->curr->type == AND_IF || \
		lst->curr->type == OR_IF)
		{
			lst->curr = lst->curr->next;
			break ;
		}
		lst->curr = lst->curr->next;
	}
}
