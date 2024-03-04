/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_goto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:46:42 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 18:58:39 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

int	lalr_goto(t_automata *at, t_table t)
{
	t_stack	*st;

	if (t.action == REJECT)
		return (REJECT);
	st = at->stack;
	st->push(st, t.number);
	return (GOTO);
}
