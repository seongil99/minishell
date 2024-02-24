/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_shift.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:46:32 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 18:58:55 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

int	lalr_shift(t_automata *at, t_table t)
{
	t_stack		*st;
	t_gmr_var	var;

	if (t.action == REJECT)
		return (REJECT);
	st = at->stack;
	var = ((t_token *)at->head->data)->type;
	st->push(st, var);
	st->push(st, t.number);
	return (SHIFT);
}
