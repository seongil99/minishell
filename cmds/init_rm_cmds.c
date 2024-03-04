/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rm_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:31:25 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 09:28:07 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (del->file_heredoc)
			unlink(del->file_heredoc);
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
}

void	init_pipe(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
		{
			pipe(tmp->pipefd);
		}
		tmp = tmp->next;
	}
}

void	close_pipe(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
		}
		tmp = tmp->next;
	}
}

void	close_pipe_re(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
			close(tmp->pipefd[0]);
		tmp = tmp->next;
	}
}
