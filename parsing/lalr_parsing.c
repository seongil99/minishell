/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:07:24 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:09:29 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

int	lalr_action(t_automata *at, t_stack *st, t_table t)
{
	int	ret;

	ret = 0;
	if (t.action == REDUCE)
		ret = lalr_reduce(at, st, t);
	else if (t.action == SHIFT)
		ret = lalr_shift(at, st, t);
	return (ret);
}

t_treenode	*parse_line(t_lst *lst)
{
	t_automata	*atmt;
	t_stack		*st;
	t_treenode	*root;
	int			t;

	atmt = automata_new(lst);
	st = stack_new();
	while (true)
	{
		t = auto_transition(atmt, st);
		if (t == ACC || t == REJECT)
			break ;
	}
	automata_del(atmt);
	root = st->top(st);
	st->pop(st, do_nothing);
	stack_del(st, free);
	if (root->data->type == AND_OR)
		return (root);
	return (NULL);
}
