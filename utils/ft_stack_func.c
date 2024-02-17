/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:01:45 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:02:36 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "mini_utils.h"

void	*stack_top(t_stack *st)
{
	if (!st->_top)
		exit_err("Error: attempted to top() empty stack\n");
	return (st->_top->data);
}

void	stack_push(t_stack *st, int n)
{
	t_lst	*new;
	int		*data;

	data = ft_calloc2(1, sizeof(int));
	*data = n;
	new = lst_new(data);
	if (!st->_btm)
	{
		st->_top = new;
		st->_btm = new;
	}
	else
	{
		st->_top->next = new;
		new->prev = st->_top;
		new->next = NULL;
		st->_top = new;
	}
	st->size++;
}

void	stack_push_void(t_stack *st, void *data)
{
	t_lst	*new;

	new = lst_new(data);
	if (!st->_btm)
	{
		st->_top = new;
		st->_btm = new;
	}
	else
	{
		st->_top->next = new;
		new->prev = st->_top;
		new->next = NULL;
		st->_top = new;
	}
	st->size++;
}

void	stack_pop(t_stack *st, void (*f)(void *))
{
	t_lst	*t;

	if (st->size == 0)
	{
		write(STDERR_FILENO, "Error: attempted to pop() empty stack\n", 38);
		exit(1);
	}
	t = st->_top;
	if (st->size == 1)
	{
		lst_del(&(st->_btm), t, f);
		st->_top = NULL;
		st->_btm = NULL;
		st->size--;
		return ;
	}
	st->_top = st->_top->prev;
	lst_del(&(st->_btm), t, f);
	st->_top->next = NULL;
	st->size--;
}
