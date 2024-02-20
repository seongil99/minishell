/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:58 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/20 16:48:47 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_for_logic(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

t_cmd_node	*get_prev_cmd_for_logic(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd_for_logic(ret))
		ret = ret->prev;
	while (ret && is_cmd_for_logic(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

int	logic_stop(t_cmd_lst *lst)
{
	if (lst->curr->prev && !ft_strncmp(lst->curr->prev->token, "||", 3))
		if (g_exit_code == 0)
			return (1);
	if (lst->curr->prev && !ft_strncmp(lst->curr->prev->token, "&&", 3))
		if (g_exit_code != 0)
			return (1);
	return (0);
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
		args = get_cmd_args(lst);
		if (get_next_cmd_pp(lst) && !ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<", 1))
			redi_left(lst, envlst, envp);
		else if (get_prev_cmd_for_logic(lst))
			dup2(get_prev_cmd_for_logic(lst)->pipefd[0], STDIN_FILENO);
		close_pipe(lst);
		if (!builtin_choice(lst, envlst))
			exec_program(envlst, args, envp);
		exit(g_exit_code); // 빌트인 실패시에 대한 errno설정 필요
	}
	waitpid(pid, &g_exit_code, 0);
}
