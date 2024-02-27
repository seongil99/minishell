/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:58 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 11:06:04 by sihkang          ###   ########seoul.kr  */
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
	if (lst->curr->type == WORD)
	{
		close(lst->curr->pipefd[0]);
		close(lst->curr->pipefd[1]);
	}
	waitpid(pid, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
}

void	logic_control(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	char	**args;
	pid_t	pid;

	if (logic_stop(lst))
		return ;
	pid = fork();
	if (pid == 0)
	{
		args = get_cmd_args_pp(lst);
		if (args[0] == NULL)
			exit(0);
		if (left_redirect_condition(lst))
			redi_left(lst);
		else if (new_get_prev_cmd(lst))
			dup2(lst->curr->pipefd[0], STDIN_FILENO);
		close_pipe(lst);
		if (right_redirect_condition(lst))
			redi_right(lst, envlst, envp);
		else if (!builtin_choice(lst, envlst))
			exec_program(envlst, args, envp);
		exit(g_exit_code);
	}
	logic_post_processing(lst, pid);
}
