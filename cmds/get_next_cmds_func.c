/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmds_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:12 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 13:48:25 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*get_next_cmd_pp(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_pp(ret))
		ret = ret->next;
	if (ret && (ret->type == AND_IF || ret->type == OR_IF))
		return (NULL);
	if (ret)
		ret = ret->next;
	return (ret);
}

t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}
	while (ret && is_cmd_after_lr(ret))
		ret = ret->next;
	while (ret && ret->type != WORD)
		ret = ret->next;
	if (!ret)
		return (NULL);
	else
		return (ret);
}

t_cmd_node	*new_get_next_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	ret = lst->curr;
	if (!ret->next)
		return (NULL);
	while (ret && (ret->type == WORD || \
	ret->type == LESS || ret->type == DLESS))
		ret = ret->next;
	if (!ret)
		return (NULL);
	while (ret && ret->type != WORD)
	{
		if (ret->type == AND_IF || ret->type == OR_IF)
			return (NULL);
		ret = ret->next;
	}
	if (!ret)
		return (NULL);
	else
		return (ret);
}

t_cmd_node	*get_next_cmd_for_move(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_for_move(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}
