/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:33:58 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 10:43:42 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (lst->curr != lst->head)
			dup2(get_prev_cmd(lst)->pipefd[0], STDIN_FILENO);
		close_pipe(lst);
		if (!builtin_choice(lst, envlst))
		{
			execve(lst->curr->token, args, envp);
			perror("minishell pipe line");
			exit(g_exit_code);
		}
		exit(g_exit_code); // 빌트인 실패시에 대한 errno설정 필요
	}
	waitpid(pid, &g_exit_code, 0);
}
