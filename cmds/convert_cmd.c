/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:20:45 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/27 20:05:09 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd_node	*cmd_node_new(char	*token, t_gmr_var type)
{
	t_cmd_node	*ret;

	ret = ft_calloc2(1, sizeof(t_cmd_node));
	ret->token = ft_strdup(token);
	ret->type = type;
	return (ret);
}

static t_cmd_node	*cmdlst_last(t_cmd_node	*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	cmdlst_push_back(t_cmd_lst *lst, t_cmd_node *newlst)
{
	t_cmd_node	*last;

	if (!lst || !newlst)
		return ;
	if (!(lst->head))
	{
		lst->head = newlst;
		lst->curr = newlst;
		lst->tail = newlst;
		lst->nums = 1;
	}
	else
	{
		last = cmdlst_last(lst->head);
		last->next = newlst;
		newlst->prev = last;
		lst->tail = newlst;
		lst->nums++;
	}
}

/**
 * token 리스트를 받아 cmd 리스트로 변환
 * @param lst token 리스트
 * @return cmd 리스트
*/
t_cmd_lst	*convert_cmd(t_lst	*lst)
{
	t_cmd_lst	*ret;
	t_token		*t;

	if (!lst)
		return (NULL);
	ret = ft_calloc2(1, sizeof(t_cmd_lst));
	while (lst)
	{
		t = lst->data;
		cmdlst_push_back(ret, cmd_node_new(t->str, t->type));
		lst = lst->next;
	}
	return (ret);
}
