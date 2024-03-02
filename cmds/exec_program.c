/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:33:46 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/02 16:25:22 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_with_dir(t_env_lst *envlst, char **args, char **envp)
{
	char	**path;
	char	*add_slash;
	char	*ab_path;
	int		i;

	i = 0;
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

int	exec_program(t_env_lst *envlst, char **args, char **envp)
{
	if (args[0] == NULL)
		exit(0);
	if (!ft_strchr(args[0], '/'))
		exec_with_dir(envlst, args, envp);
	else if (ft_strchr(args[0], '/'))
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

void	cmd_pre_process(t_cmd_lst *lst, t_env_lst *envlst)
{
	lst_reordering(lst);
	init_pipe(lst);
	get_heredoc(lst, envlst);
}

void	set_program_envir(t_cmd_lst *lst, t_env_lst *envlst, \
						struct termios org_term)
{
	reset_input_mode(&org_term);
	signal(SIGINT, signal_exec);
	signal(SIGQUIT, signal_exec);
	update_underbar(lst, envlst);
}

void	cmd_post_process(t_cmd_lst *lst, pid_t proc_id)
{
	close_pipe(lst);
	if (waitpid(proc_id, &g_exit_code, 0) != -1)
		g_exit_code = WEXITSTATUS(g_exit_code);
	while (wait(0) != -1)
	{
	}
}
