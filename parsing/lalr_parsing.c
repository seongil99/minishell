/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:07:24 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 12:58:50 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalr_parser.h"
#include "lalr_table.h"
#include "scanner.h"

t_automata	*automata_new(t_lst *input)
{
	t_automata	*new_at;

	new_at = ft_calloc2(1, sizeof(t_automata));
	new_at->head = input;
	new_at->stack = stack_new();
	new_at->stack->push(new_at->stack, 0);
	return (new_at);
}

void	automata_del(t_automata *at)
{
	stack_del(at->stack);
	free(at);
}

int	auto_get_state(t_automata *at)
{
	t_lst	*t;
	int		state;

	t = at->stack->_top;
	state = 0;
	while (t)
	{
		state = *(int *)t->data;
		if (state < 100)
			break ;
		t = t->prev;
	}
	return (state);
}

int	auto_move(t_automata *at, int state, int top, t_gmr_var head)
{
	int	ret;

	ret = 0;
	if (top < 100)
		lalr_action();
	else
		lalr_goto();
	return (ret);
}

int	auto_transition(t_automata *at)
{
	int			cur_state;
	int			st_top;
	t_gmr_var	*input_head;

	cur_state = auto_get_state(at);
	st_top = stack_top(at->stack);
	input_head = ((t_token *)at->head->data)->type;
}

bool	parse_line(t_lst *lst)
{
	t_automata	*atmt;

	atmt = automata_new(lst);
}
