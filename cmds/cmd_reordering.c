/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_reordering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:41:05 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 09:32:42 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_cmd_to_first(t_cmd_lst *lst, t_cmd_node *tmp)
{
	t_cmd_node	*new;

	new = (t_cmd_node *)ft_calloc2(1, sizeof(t_cmd_node));
	new->token = ft_strdup(tmp->token);
	free(tmp->token);
	new->type = tmp->type;
	new->next = lst->curr;
	if (lst->curr == lst->head)
	{
		lst->head = new;
		new->prev = NULL;
		lst->curr->prev = new;
	}
	else
	{
		new->prev = lst->curr->prev;
		new->prev->next = new;
		lst->curr->prev = new;
	}
	lst->curr = new;
}

t_cmd_node	*move_to_cmd_name(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->curr->next;
	while (tmp)
	{
		if (redirect_check(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		else
			break ;
	}
	return (tmp);
}

void	relink_after_insert(t_cmd_lst *lst, t_cmd_node *tmp)
{
	if (tmp->next)
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	}
	else
	{
		lst->tail = lst->tail->prev;
		lst->tail->next = NULL;
	}
	free(tmp);
}

void	lst_reordering(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	int			n_cmd;

	n_cmd = 0;
	while (lst->curr)
	{
		while (lst->curr->type == LPAR)
			lst->curr = lst->curr->next;
		if (lst->curr->type != WORD)
		{
			if (!is_cmd_for_move(lst->curr))
				n_cmd++;
			tmp = move_to_cmd_name(lst);
			if (tmp == NULL)
				break ;
			if (tmp->type == WORD)
			{
				swap_cmd_to_first(lst, tmp);
				relink_after_insert(lst, tmp);
			}
		}
		lst->curr = get_next_cmd_for_move(lst);
	}
	if (n_cmd > 50)
		return (1);
	lst->curr = lst->head;
}
