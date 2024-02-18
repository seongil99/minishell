/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_shift.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:46:32 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:17:43 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

int	lalr_shift(t_automata *at, t_stack *tree_stack, t_table t)
{
	t_stack		*st;
	t_gmr_var	var;
	t_treenode	*node;

	if (t.action == REJECT)
		return (REJECT);
	st = at->stack;
	var = ((t_token *)at->head->data)->type;
	st->push(st, var);
	st->push(st, t.number);
	node = treenode_new(token_dup(at->head->data));
	tree_stack->push_void(tree_stack, node);
	return (SHIFT);
}
