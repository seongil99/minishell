/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/22 10:58:01 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_choice(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (builtin_env(envlst));
	else if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (builtin_unset(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "export", 7))
		return (builtin_export(lst, envlst));
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

int	is_builtin(t_cmd_lst *lst)
{
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "export", 7))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "echo", 5))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "cd", 3))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "pwd", 4))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "exit", 5))
		return (1);
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
		exit(g_exit_code);
	}
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
	perror("minishell program failed");
	exit(g_exit_code);
}

int	is_cmd_for_check_logic(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

t_cmd_node	*get_next_cmd_for_check_logic(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_for_check_logic(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

int	is_cmd_after_lr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

t_cmd_node	*get_next_cmd_after_lr(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_after_lr(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

char	*last_args(t_cmd_lst *lst)
{
	char	**args;
	int		i;

	i = 0;
	args = get_cmd_args(lst);
	while (args[i])
		i++;
	return (args[i - 1]);
}

void	run_commands(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int			proc_id;
	int			n_pid;
	
	n_pid = 0;
	init_pipe(lst);
	get_heredoc(lst);
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
			if (!get_prev_cmd_rr(lst) && !get_next_cmd_pp(lst) && \
			is_builtin(lst))
			{
				envlst->underbar->value = last_args(lst);
				builtin_choice(lst, envlst);
			}
			else if ((get_next_cmd_for_check_logic(lst) && \
				(!ft_strncmp(get_next_cmd_for_check_logic(lst)->prev->token, "&&", 3) || \
				!ft_strncmp(get_next_cmd_for_check_logic(lst)->prev->token, "||", 3))))
				logic_control(lst, envlst, envp);
			else
			{
				proc_id = fork();
				if (proc_id == 0)
				{
					if (get_next_cmd_pp(lst) && !ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<", 1))
						redi_left(lst, envlst, envp);
					else if (get_prev_cmd_rr(lst))
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
			move_to_next_cmd(lst);
		}
	}
	close_pipe(lst);
	while (n_pid--)
		wait(0);
}
