/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:45:10 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 20:05:02 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == WORD);
}

int	is_cmd_for_move(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type != AND_IF && \
			node->type != OR_IF && \
			node->type != PIPE);
}

int	is_cmd_pp(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == WORD || node->type == LPAR || node->type == RPAR);
}

int	is_cmd_after_lr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type != DGREAT && \
			node->type != GREAT && \
			node->type != AND_IF && \
			node->type != OR_IF && \
			node->type != PIPE);
}

int	is_cmd_for_check_logic(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == DGREAT || \
			node->type == GREAT || \
			node->type == AND_IF || \
			node->type == OR_IF || \
			node->type == PIPE);
}
