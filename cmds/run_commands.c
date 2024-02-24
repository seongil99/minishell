/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/24 20:30:20 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_program(t_env_lst *envlst, char **args, char **envp)
{
	char	**path;
	int		i;
	char	*ab_path;
	char	*add_slash;
	i = 0;

	if (!ft_strchr(args[0], '/'))
	{
		if (envlst->path)
		{
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
		}
	}
	else
	{
		if (!access(args[0], F_OK & X_OK))
		{
			execve(args[0], args, envp);
			perror("minishell program executed");
			exit(126);
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
	proc_id = 0;
	init_pipe(lst);
	get_heredoc(lst, envlst);
	if (g_exit_code == 0)
	{
		while (lst->curr)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (!ft_strncmp(lst->curr->token, "(", 2))
			{
				exec_subshell(lst);
				continue ;
			}
			update_underbar(lst, envlst);
			if (is_builtin(lst) && (!get_prev_cmd_rr(lst) && !get_next_cmd_pp(lst)))
				builtin_choice(lst, envlst);
			else
			{
				if (is_logical(lst->curr))
					logic_control(lst, envlst, envp);
				else
				{
					proc_id = fork();
					if (proc_id == 0)
					{
						if (get_next_cmd_pp(lst) && !ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<", 1))
							redi_left(lst, envlst, envp);
						else if (new_get_prev_cmd(lst))
							dup2(lst->curr->pipefd[0], STDIN_FILENO);
						if (get_next_cmd_after_lr(lst) && \
						!ft_strncmp(get_next_cmd_after_lr(lst)->prev->token, ">", 1))
							redi_right(lst, envlst, envp);
						else
							pipe_exec(lst, envlst, envp);
						exit(g_exit_code);
					}
					else
					{
						signal(SIGINT, SIG_IGN);
						signal(SIGQUIT, SIG_IGN);
					}
					n_pid++;
				}
			}
			move_to_next_cmd(lst);
		}
		close_pipe(lst);
		waitpid(proc_id, &g_exit_code, 0);
		g_exit_code = WEXITSTATUS(g_exit_code);
		while (n_pid--)
		{
			wait(0);
		}
	}	
}
