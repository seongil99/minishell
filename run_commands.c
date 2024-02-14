/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/14 09:55:20 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_cmd(t_lst *lst, char **tokens)
{
	t_node	*new;
	int		i;

	i = 0;
	while (tokens[i])
	{
		new = (t_node *)ft_calloc(sizeof(t_node), 1);
		new->token = tokens[i];
		if (i++ == 0)
		{
			lst->head = new;
			lst->tail = new;
			lst->curr = new;
			new->next = NULL;
			new->prev = NULL;
		}
		else
		{
			lst->tail->next = new;
			new->prev = lst->tail;
			lst->tail = new;
			new->next = NULL;
		}
		lst->nums++;
	}
}

void	init_pipe(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if (ft_strncmp(tmp->token, "|", 2))
			pipe(tmp->pipefd);
		tmp = tmp->next;
	}
}

void	close_pipe(t_lst *lst)
{
	t_node	*tmp;
	
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

void	pipe_exec(t_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	*args[2];

	args[0] = "asdf1";
	args[1] = NULL;
	if (lst->curr != lst->tail)
		dup2(lst->curr->pipefd[1], STDOUT_FILENO);
	if (lst->curr != lst->head)
		dup2(lst->curr->prev->prev->pipefd[0], STDIN_FILENO);
	close_pipe(lst);
	if (!builtin_choice(lst, envlst))
		execve(lst->curr->token, args, envp);
	perror("minishell pipe line");
}

int	builtin_choice(t_lst *lst, t_env_lst *envlst)
{
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (builtin_env(envlst));
	if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (builtin_unset(envlst, lst->curr->next->token));
	if (!ft_strncmp(lst->curr->token, "export", 7))
		return (builtin_export(envlst, lst->curr->next->token));
	if (!ft_strncmp(lst->curr->token, "echo", 5))
		return (builtin_echo(lst));
	if (!ft_strncmp(lst->curr->token, "cd", 3))
		return (builtin_cd(lst));
	if (!ft_strncmp(lst->curr->token, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(lst->curr->token, "exit", 5))
		builtin_exit(lst);
	return (0);
}

void	run_commands(char **tokens, t_lst *lst, t_env_lst *envlst, char **envp)
{
	int		proc_id;
	
	push_cmd(lst, tokens);
	init_pipe(lst);
	while (lst->curr)
	{
		if (ft_strncmp(lst->curr->token, "<<", 3) && \
			ft_strncmp(lst->curr->token, "<", 2) && \
			ft_strncmp(lst->curr->token, ">>", 3) && \
			ft_strncmp(lst->curr->token, ">", 2) && \
			ft_strncmp(lst->curr->token, "|", 2))
		{
			proc_id = fork();
			if (proc_id == 0)
			{
				if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, ">", 1))
					redi_right(lst, envlst, envp);
				else if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, "<", 1))
					redi_left(lst, envlst, envp);
				else
					pipe_exec(lst, envlst, envp);
			}
		}
		lst->curr = lst->curr->next;
	}
	close_pipe(lst);
	while (lst->nums--)
		wait(0);
}
