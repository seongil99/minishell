/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rm_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:31:25 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 15:40:19 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_cmd(t_cmd_lst *lst, char **tokens)
{
	t_cmd_node	*new;
	int		i;

	i = 0;
	while (tokens[i])
	{
		new = (t_cmd_node *)ft_calloc2(sizeof(t_cmd_node), 1);
		new->token = ft_strdup(tokens[i]);
		new->file_heredoc = NULL;
		free(tokens[i]);
		new->next = NULL;
		if (i++ == 0)
		{
			lst->head = new;
			new->prev = NULL;
		}
		else
		{
			lst->tail->next = new;
			new->prev = lst->tail;
		}
		lst->tail = new;
		lst->nums++;
	}
	free(tokens);
}

void	clear_lst(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	t_cmd_node	*del;

	if (!lst)
		return ;
	tmp = lst->head;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		free(del->token);
		del->token = 0;
		free(del->file_heredoc);
		del->file_heredoc = 0;
		free(del);
		del = 0;
	}
	lst->head = 0;
	lst->tail = 0;
	lst->curr = 0;
	free(lst);
	return ;
}
