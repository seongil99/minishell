/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:20:21 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 18:06:20 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "mini_utils.h"

void	lst_push_front(t_lst **head, t_lst *newlst)
{
	if (!head || !newlst)
		return ;
	if (!(*head))
		*head = newlst;
	else
	{
		newlst->next = *head;
		(*head)->prev = newlst;
		*head = newlst;
		newlst->prev = NULL;
	}
}

void	lst_push_back(t_lst **head, t_lst *newlst)
{
	t_lst	*last;

	if (!head || !newlst)
		return ;
	if (!(*head))
		*head = newlst;
	else
	{
		last = ft_lstlast(*head);
		last->next = newlst;
	}
}
