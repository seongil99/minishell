/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:07:24 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/21 14:03:21 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

int	lalr_action(t_automata *at, t_table t)
{
	int	ret;

	ret = 0;
	if (t.action == REDUCE)
		ret = lalr_reduce(at, t);
	else if (t.action == SHIFT)
		ret = lalr_shift(at, t);
	return (ret);
}

/**
 * token 리스트를 받아서 ACCEPT, REJECT 판별
 * @param lst token 리스트
 * @return ACCEPT 1, REJECT 0
*/
int	parse_line(t_lst *lst)
{
	t_automata	*atmt;
	int			t;

	if (!lst)
		return (0);
	atmt = automata_new(lst);
	while (true)
	{
		t = auto_transition(atmt);
		if (t == ACC || t == REJECT)
			break ;
	}
	automata_del(atmt);
	return (t);
}
