/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:26:17 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 15:59:45 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_cmd_for_heredoc(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == WORD || \
	node->type == LPAR || node->type == RPAR || \
	node->type == GREAT || node->type == DGREAT);
}

t_cmd_node	*get_next_cmd_for_heredoc(t_cmd_node *node)
{
	if (!node->next)
	{
		node = node->next;
		return (NULL);
	}
	while (node && is_cmd_for_heredoc(node))
		node = node->next;
	if (node && (node->type == PIPE || \
	node->type == AND_IF || node->type == OR_IF))
		return (NULL);
	if (node)
		node = node->next;
	return (node);
}

void	move_to_next_cmd_heredoc(t_cmd_lst *lst)
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
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
	if (lst->curr && !is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
}
