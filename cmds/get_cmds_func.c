/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:47:12 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/23 16:18:40 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*get_next_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

t_cmd_node	*get_prev_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd(ret))
		ret = ret->prev;
	while (ret && is_cmd(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

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
	if (ret)
		ret = ret->next;
	return (ret);
}

t_cmd_node	*get_prev_cmd_pp(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd_pp(ret))
		ret = ret->prev;
	while (ret && is_cmd_pp(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

t_cmd_node	*get_next_cmd_for_check_logic(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_for_check_logic(ret))
		ret = ret->next;
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
	if (ret)
		ret = ret->next;
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
