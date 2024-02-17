/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 20:09:45 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:02:14 by seonyoon         ###   ########.fr       */
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
	st->push_void = stack_push_void;
	return (st);
}

void	stack_del(t_stack *st, void (*f)(void *))
{
	lst_clear(&(st->_btm), f);
	st->_top = NULL;
	st->_btm = NULL;
	free(st);
}
