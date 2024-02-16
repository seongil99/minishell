/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_goto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:46:42 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/16 16:05:53 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalr_parser.h"
#include "lalr_table.h"
#include "scanner.h"

int	lalr_goto(t_automata *at, t_table t)
{
	t_stack	*st;

	if (t.action == REJECT)
		return (REJECT);
	st = at->stack;
	st->push(st, t.number);
	printf("GOTO %d\n", t.number);
	return (GOTO);
}
