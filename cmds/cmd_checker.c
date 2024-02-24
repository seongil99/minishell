/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:45:10 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/24 19:14:57 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "(", 2) && \
			ft_strncmp(node->token, ")", 2) && \
			ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

int	is_cmd_for_args(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2) && \
			ft_strncmp(node->token, ")", 2));
}


int	is_cmd_for_move(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

int	is_cmd_pp(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && 
			ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

int	is_cmd_after_lr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

int	is_cmd_for_check_logic(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}
