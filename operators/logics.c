/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:58 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/02 11:17:03 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_for_logic(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type != AND_IF && \
			node->type != OR_IF && \
			node->type != PIPE);
}

int	logic_stop(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->curr;
	while (tmp && (tmp->type != AND_IF && tmp->type != OR_IF))
		tmp = tmp->prev;
	if (!tmp)
		return (0);
	if (tmp->type == OR_IF)
	{
		if (g_exit_code == 0)
			return (1);
	}
	else if (tmp->type == AND_IF)
	{
		if (g_exit_code != 0)
			return (1);
	}
	return (0);
}

void	logic_post_processing(t_cmd_lst *lst, pid_t pid)
{
	t_cmd_node	*tmp;

	tmp = lst->curr;
	// printf("waiting pid %d\n", pid);
	close_pipe(lst);
	waitpid(pid, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	// while (wait(0) != -1)
	// {
	// }
	// printf("waiting g_exit_code %d\n", g_exit_code);
	init_pipe(lst);
}

void	logic_control(t_cmd_lst *lst, t_env_lst *envlst, char **envp, pid_t *proc_id)
{
	if (logic_stop(lst))
		return ;
	*proc_id = fork();
	if (*proc_id == 0)
	{
		// pipe(lst->curr->pipefd);
		if (left_redirect_condition(lst))
			redi_left(lst);
		else if (new_get_prev_cmd(lst))
			dup2(lst->curr->pipefd[0], STDIN_FILENO);
		if (right_redirect_condition(lst))
			redi_right(lst, envlst, envp);
		else
			pipe_exec(lst, envlst, envp);
	}
	logic_post_processing(lst, *proc_id);
}
