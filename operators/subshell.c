/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:29:07 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 16:23:19 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child_process(pid_t id)
{
	waitpid(id, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	while (wait(0) != -1)
	{
	}
}

void	exec_subshell(t_cmd_lst *lst)
{
	static int	num = 0;
	pid_t		id;

	id = fork();
	if (id == 0)
	{
		num++;
		if (logic_stop(lst))
			exit(g_exit_code);
		lst->curr = lst->curr->next;
		return ;
	}
	else
		move_to_close_subshell(lst, id);
	if (num != 0)
	{
		wait_child_process(id);
		exit(g_exit_code);
	}
}

void	end_subshell(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->curr;
	while (tmp && tmp->type != PIPE && \
	tmp->type != AND_IF && tmp->type != OR_IF)
	{
		if (tmp->type == RPAR)
		{
			while (wait(0) != -1)
			{
			}
			exit(g_exit_code);
		}
		tmp = tmp->next;
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
			wait_child_process(id);
		tmp = tmp->next;
		if (tmp->type == WORD || tmp->type == LPAR)
			break ;
	}
	lst->curr = tmp;
}
