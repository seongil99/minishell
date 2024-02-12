/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:09:45 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 18:23:22 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "mini_utils.h"

t_stack	*stack_new(void)
{
	t_stack	*st;

	st = ft_calloc2(1, sizeof(t_stack));
	st->pop = stack_pop;
	st->push = stack_push;
	st->top = stack_top;
	return (st);
}

void	stack_del(t_stack *st)
{
	lst_clear(&(st->_btm));
	st->_top = NULL;
	st->_btm = NULL;
	free(st);
}

int	stack_top(t_stack *st)
{
	int	*t;

	if (!st->_top)
		exit_err("Error: attempted to top() empty stack\n");
	t = (int *)st->_top->data;
	return (*t);
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

void	stack_pop(t_stack *st)
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
		lst_del(&(st->_btm), t);
		st->_top = NULL;
		st->_btm = NULL;
		st->size--;
		return ;
	}
	st->_top = st->_top->prev;
	lst_del(&(st->_btm), t);
	st->_top->next = NULL;
	st->size--;
}
