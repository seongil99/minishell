/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prev_cmd_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:02:08 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 13:48:27 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*new_get_prev_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (ret && ret->type != WORD)
	{
		if (ret->type == AND_IF || ret->type == OR_IF)
			return (NULL);
		ret = ret->prev;
	}
	while (ret && ret->type == WORD)
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	if (!ret)
		return (NULL);
	else
		return (ret->next);
}

int	is_logical(t_cmd_node *ret)
{
	while (ret && (ret->type == RPAR || ret->type == DGREAT || \
	ret->type == LPAR || ret->type == RPAR || \
	ret->type == DLESS || ret->type == LESS || \
	ret->type == GREAT || ret->type == WORD))
		ret = ret->next;
	if (!ret)
		return (false);
	else if (ret->type == PIPE)
		return (false);
	else
		return (true);
}
