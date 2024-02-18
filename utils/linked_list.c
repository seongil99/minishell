/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:17:56 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 16:05:21 by seonyoon         ###   ########.fr       */
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

void	lst_del(t_lst **lst, t_lst *target, void (*f)(void *))
{
	if (*lst == target)
		*lst = target->next;
	if (target->prev != NULL)
		target->prev->next = target->next;
	if (target->next != NULL)
		target->next->prev = target->prev;
	f(target->data);
	target->data = 0;
	target->next = 0;
	target->prev = 0;
	free(target);
}

void	lst_clear(t_lst **head, void (*f)(void *))
{
	t_lst	*t;
	t_lst	*n;

	t = *head;
	while (t)
	{
		n = t->next;
		f(t->data);
		t->data = 0;
		t->next = 0;
		t->prev = 0;
		free(t);
		t = n;
	}
	*head = NULL;
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

void	do_nothing(void *v)
{
	(void)v;
}
