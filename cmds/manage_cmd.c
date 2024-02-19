/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:24:06 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 12:13:57 by sihkang          ###   ########seoul.kr  */
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
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2) && \
			ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2));
}

t_cmd_node	*get_prev_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd(ret))
		ret = ret->prev;
	while (ret && is_cmd(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	if (!ft_strncmp(ret->token, "<", 2) || \
	!ft_strncmp(ret->token, "<<", 3))
		return (get_prev_cmd(lst));
	return (ret->next);
}

t_cmd_node	*get_next_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

void	move_to_next_cmd(t_cmd_lst *lst)
{
	if (!lst->curr)
		return ;
	if (!lst->curr->next)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	while (lst->curr && is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
	while (lst->curr && !is_cmd(lst->curr))
	{
		if (!ft_strncmp(lst->curr->token, "(", 2))
			exec_subshell(lst);
		else if (!ft_strncmp(lst->curr->token, ")", 2))
			exit(g_exit_code);
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
	if (lst->curr)
		if (!ft_strncmp(lst->curr->prev->token, "<", 1) || \
		!ft_strncmp(lst->curr->prev->token, ">", 1))
			move_to_next_cmd(lst);
}

char 	**get_cmd_args(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	char	**args;
	int		nums;

	nums = 0;
	tmp = lst->curr;
	while (tmp && is_cmd(tmp))
	{
		nums++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!is_cmd(tmp))
		tmp = tmp->prev;
	args = (char **)ft_calloc(nums + 1, sizeof(char *));
	args[nums--] = NULL;
	while (nums >= 0 && tmp)
	{
		args[nums--] = ft_strdup(tmp->token);
		tmp = tmp->prev;
	}
	return (args);
}
