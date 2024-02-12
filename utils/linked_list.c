/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:17:56 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 17:48:18 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "mini_utils.h"

t_lst	*lst_new(void *data)
{
	t_lst	*lst;

	lst = ft_calloc2(1, sizeof(t_lst));
	lst->data = data;
	return (lst);
}

void	lst_del(t_lst **lst, t_lst *target)
{
	if (*lst == target)
		*lst = target->next;
	if (target->prev != NULL)
		target->prev->next = target->next;
	if (target->next != NULL)
		target->next->prev = target->prev;
	free(target->data);
	target->data = 0;
	target->next = 0;
	target->prev = 0;
	free(target);
}

void	lst_clear(t_lst **head)
{
	t_lst	*t;

	t = *head;
	while (t)
	{
		t = t->next;
		free(t->prev->data);
		t->prev->data = 0;
		t->prev->next = 0;
		t->prev->prev = 0;
		free(t->prev);
	}
}

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
