/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_automata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:07:43 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 13:54:19 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

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

int	auto_action(t_automata *at, t_gmr_var head)
{
	int		ret;
	int		state;
	int		top;
	t_table	**t;

	ret = 0;
	state = auto_get_state(at);
	top = *(int *)stack_top(at->stack);
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
	t_gmr_var	input_head;
	int			ret;

	if (!at->head)
		input_head = TYPE_EOF;
	else
		input_head = ((t_token *)at->head->data)->type;
	ret = auto_action(at, input_head);
	if (at->head && ret == SHIFT)
		at->head = at->head->next;
	return (ret);
}
