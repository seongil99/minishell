/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:07:24 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 13:26:08 by seonyoon         ###   ########.fr       */
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
	stack_del(at->stack, free);
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

int	auto_action(t_automata *at, int state, int top, t_gmr_var head)
{
	int		ret;
	t_table	**t;

	ret = 0;
	if (state == 1 && head == TYPE_EOF)
		return (ACC);
	if (top < COMPLETE_COMMAND)
	{
		t = get_action_table();
		ret = lalr_action(at, t[state][head - AND_IF]);
	}
	else
	{
		t = get_goto_table();
		ret = lalr_goto(at, t[state][top - COMPLETE_COMMAND]);
	}
	return (ret);
}

int	auto_transition(t_automata *at)
{
	int			cur_state;
	int			st_top;
	t_gmr_var	input_head;
	int			ret;

	cur_state = auto_get_state(at);
	st_top = stack_top(at->stack);
	if (!at->head)
		input_head = TYPE_EOF;
	else
		input_head = ((t_token *)at->head->data)->type;
	ret = auto_action(at, cur_state, st_top, input_head);
	if (at->head && ret == SHIFT)
		at->head = at->head->next;
	return (ret);
}

int	parse_line(t_lst *lst)
{
	t_automata	*atmt;
	int			t;

	/**
	 * init functions should be called once at the minishell init
	*/
	init_action_table();
	init_goto_table();
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
