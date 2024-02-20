/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_reduce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:46:37 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/19 13:19:18 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static int	reduce_pop(t_automata *at, t_table t)
{
	int	n;
	int	i;

	n = t.number;
	if (n == 2 || n == 3 || n == 5 || n == 9)
		n = 6;
	else if (n == 8 || n == 10 || n == 14 || n == 16 || n == 18
		|| n == 21 || n == 22 || n == 23 || n == 25)
		n = 4;
	else
		n = 2;
	i = 0;
	while (i < n)
	{
		stack_pop(at->stack, free);
		++i;
	}
	return (n / 2);
}

static void	reduce_push1(t_stack *st, int n)
{
	if (n == 0)
		st->push(st, COMPLETE_COMMAND);
	else if (1 <= n && n <= 3)
		st->push(st, AND_OR);
	else if (n == 4 | n == 5)
		st->push(st, PIPELINE);
	else if (6 <= n && n <= 8)
		st->push(st, COMMAND);
	else if (n == 9)
		st->push(st, SUBSHELL);
	else if (n == 10 || n == 11)
		st->push(st, SIMPLE_COMMAND);
	else if (n == 12)
		st->push(st, CMD_NAME);
	else if (13 <= n && n <= 16)
		st->push(st, CMD_SUFFIX);
}

static void	reduce_push2(t_stack *st, int n)
{
	if (n == 17 || n == 18)
		st->push(st, REDIRECTION_LIST);
	else if (n == 19 || n == 20)
		st->push(st, IO_REDIRECT);
	else if (21 <= n && n <= 23)
		st->push(st, IO_FILE);
	else if (n == 24)
		st->push(st, FILENAME);
	else if (n == 25)
		st->push(st, IO_HERE);
	else if (n == 26)
		st->push(st, HERE_END);
}

static void	reduce_push(t_automata *at, t_table t)
{
	int		n;
	t_stack	*st;

	n = t.number;
	st = at->stack;
	if (0 <= n && n <= 16)
		reduce_push1(st, n);
	else if (17 <= n && n <= 26)
		reduce_push2(st, n);
}

int	lalr_reduce(t_automata *at, t_table t)
{
	if (t.action == REJECT)
		return (REJECT);
	reduce_pop(at, t);
	reduce_push(at, t);
	return (REDUCE);
}
