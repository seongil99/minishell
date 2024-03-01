/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:29:07 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/01 21:02:51 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child_process(t_cmd_lst *lst, pid_t id)
{
	(void)lst;
	// close_pipe(lst);
	if (waitpid(id, &g_exit_code, 0) != -1)
		g_exit_code = WEXITSTATUS(g_exit_code);
	while (wait(0) != -1)
	{
	}
}
// if (logic_stop(lst))
// 		{
// 			close_pipe(lst);
// 			exit(g_exit_code);
// 		}
// 		lst->curr = lst->curr->next;
// 		tmp = lst->curr;
// 		while (tmp->type == LPAR)
// 			tmp = tmp->next;
// 		if (tmp->type == WORD && (tmp->prev == NULL || tmp->prev->type != WORD))
// 		{
// 			cmd = tmp;
// 			while (tmp && is_cmd_for_move(tmp))
// 				tmp = tmp->next;
// 			if (tmp && tmp->type != PIPE)
// 			{
// 				close(cmd->pipefd[0]);
// 				close(cmd->pipefd[1]);
// 			}
// 		}

void	exec_subshell(t_cmd_lst *lst, pid_t *id)
{
	static int	num = 0;

	*id = fork();
	if (*id == 0)
	{
		num++;
		if (logic_stop(lst))
		{
			close_pipe(lst);
			exit(g_exit_code);
		}
		lst->curr = lst->curr->next;
		return ;
	}
	move_to_close_subshell(lst, *id);
	if (num != 0)
	{
		wait_child_process(lst, *id);
		close_pipe(lst);
		exit(g_exit_code);
	}
}

t_cmd_node	*logic_with_ss(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->curr;
	while (tmp)
	{
		if ((tmp->type == LPAR) && tmp->prev && \
		(tmp->prev->type == AND_IF || tmp->prev->type == OR_IF))
			return (tmp->prev);
		tmp = tmp->prev;
	}
	return (0);
}

void	move_to_close_subshell(t_cmd_lst *lst, pid_t id)
{
	t_cmd_node	*tmp;
	int			num_ss;

	num_ss = 1;
	tmp = lst->curr->next;
	while (tmp && num_ss)
	{
		if (tmp->type == LPAR)
			num_ss++;
		else if (tmp->type == RPAR)
			num_ss--;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->type == AND_IF || tmp->type == OR_IF)
			wait_child_process(lst, id);
		tmp = tmp->next;
		if (tmp->type == WORD || tmp->type == LPAR)
			break ;
	}
	lst->curr = tmp;
	if (tmp && tmp->type == WORD && (tmp->prev->type == LESS || \
	tmp->prev->type == DLESS || tmp->prev->type == GREAT || \
	tmp->prev->type == DGREAT))
		lst->curr = get_next_cmd_pp(lst);
}
