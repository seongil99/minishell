/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 12:48:51 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_choice(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (builtin_env(envlst));
	else if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (builtin_unset(envlst, lst->curr->next->token));
	else if (!ft_strncmp(lst->curr->token, "export", 7))
		return (builtin_export(envlst, lst->curr->next->token));
	else if (!ft_strncmp(lst->curr->token, "echo", 5))
		return (builtin_echo(lst));
	else if (!ft_strncmp(lst->curr->token, "cd", 3))
		return (builtin_cd(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(lst->curr->token, "exit", 5))
		builtin_exit(lst);
	return (0);
}

int		exec_program(t_env_lst *envlst, char **args, char **envp)
{
	char	**path;
	int		i;
	char	*ab_path;
	char	*add_slash;

	if (!access(args[0], F_OK & X_OK))
	{
		execve(args[0], args, envp);
		perror("minishell program executed");
		exit(127);
	}
	i = 0;
	path = ft_split(envlst->path->value, ':');
	add_slash = ft_strjoin("/", args[0]);
	while (path[i])
	{
		ab_path = ft_strjoin(path[i++], add_slash);
		if (!access(ab_path, F_OK & X_OK))
		{
			execve(ab_path, args, envp);
			break ;
		}
	}
	perror("minishell program failed");
	exit(127);
}

void	run_commands(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int			proc_id;
	int			n_pid;
	
	n_pid = 0;
	init_pipe(lst);
	get_heredoc(lst);
	while (lst->curr)
	{
		if (lst->curr != lst->tail && \
			(!ft_strncmp(lst->curr->next->token, "&&", 3) || \
			!ft_strncmp(lst->curr->next->token, "||", 3)))
			logic_control(lst, envlst, envp);
		else
		{
			proc_id = fork();
			if (proc_id == 0)
			{
				if (get_next_cmd(lst) && !ft_strncmp(get_next_cmd(lst)->prev->token, ">", 1))
					redi_right(lst, envlst, envp);
				else
					pipe_exec(lst, envlst, envp);
			}
			n_pid++;
		}
		move_to_next_cmd(lst);
	}
	close_pipe(lst);
	while (n_pid--)
		wait(0);
}
