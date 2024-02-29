/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rm_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:31:25 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/29 22:13:49 by sihkang          ###   ########seoul.kr  */
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
	// printf("pid %d opened fds : ", getpid());
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
		{
			pipe(tmp->pipefd);
			// printf("%s : %d %d | ", tmp->token, tmp->pipefd[0], tmp->pipefd[1]);
		}
		tmp = tmp->next;
	}
	// printf("\n");
}

void	close_pipe(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->head;
	// printf("pid %d closed fds : ", getpid());
	while (tmp)
	{
		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
			// printf("%s : %d %d | ", tmp->token, tmp->pipefd[0], tmp->pipefd[1]);
		}
		tmp = tmp->next;
	}
	// printf("\n");
}

void	exit_subshell(t_cmd_lst *lst, pid_t	proc_id)
{
	// (void)proc_id;
	// printf("pid %d subshell closed\n", getpid());
	close_pipe(lst);
	waitpid(proc_id, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	while (wait(0) != -1)
	{
	}
	exit(g_exit_code);
}

int	is_cmd_close_ss(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == WORD || node->type == LPAR);
}
