/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:29:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 11:36:31 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if (ft_strncmp(tmp->token, "|", 2))
			pipe(tmp->pipefd);
		tmp = tmp->next;
	}
}

void	close_pipe(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	
	tmp = lst->head;
	while (tmp)
	{
		if (ft_strncmp(tmp->token, "|", 2))
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
		}
		tmp = tmp->next;
	}
}

void	pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;
	
	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args(lst);
	if (get_next_cmd(lst) && ft_strncmp(get_next_cmd(lst)->prev->token, "<", 1))
		dup2(lst->curr->pipefd[1], STDOUT_FILENO);
	if (get_next_cmd(lst) && !ft_strncmp(get_next_cmd(lst)->prev->token, "<", 1))
		redi_left(lst, envlst, envp);
	else if (lst->curr != lst->head)
		dup2(get_prev_cmd(lst)->pipefd[0], STDIN_FILENO);
	close_pipe(lst);
	if (!builtin_choice(lst, envlst))
		exec_program(envlst, args, envp);
	exit(0);
}
