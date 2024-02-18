/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/17 18:52:27 by sihkang          ###   ########seoul.kr  */
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
		new = (t_node *)ft_calloc2(sizeof(t_node), 1);
		new->token = ft_strdup(tokens[i]);
		free(tokens[i]);
		if (i++ == 0)
		{
			lst->head = new;
			lst->tail = new;
			lst->curr = lst->head;
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
	free(tokens);
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

int is_next_cmd(t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->curr;
	while (tmp && ft_strncmp(tmp->token, "|", 2) \
			&& ft_strncmp(tmp->token, ">>", 3) \
			&& ft_strncmp(tmp->token, ">", 2) \
			&& ft_strncmp(tmp->token, "<<", 3) \
			&& ft_strncmp(tmp->token, "<", 2))
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	return (1);
}

void	pipe_exec(t_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;

	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args(lst);
	printf("%s %s \n", args[0], args[1]);
	if (is_next_cmd(lst)) // 우측에 결과를 전달받을 파일이 있는지를 확인하는 걸로 변경 필요.
		dup2(lst->curr->pipefd[1], STDOUT_FILENO);
	if (lst->curr != lst->head)
		dup2(get_prev_cmd(lst)->pipefd[0], STDIN_FILENO);
	close_pipe(lst);
	if (!builtin_choice(lst, envlst))
	{
		execve(args[0], args, envp);
		perror("minishell pipe line");
		exit(127);
	}
	exit(0);
}

int	builtin_choice(t_lst *lst, t_env_lst *envlst)
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

int	is_op(t_node *node)
{
	return (ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

void	clear_lst(t_lst *lst)
{
	t_node	*tmp;
	t_node	*del;

	tmp = lst->head;
	while (tmp)
	{	
		del = tmp;
		tmp = tmp->next;
		free(del->token);
		del->token = 0;
		free(del);
		del = 0;
	}
	return ;
}

t_node	*get_prev_cmd(t_lst *lst)
{
	t_node	*ret;

	ret = lst->curr->prev->prev;
	while (ret && \
			ft_strncmp(ret->token, "|", 2) && \
			ft_strncmp(ret->token, ">", 1) && \
			ft_strncmp(ret->token, "<", 1) && \
			ft_strncmp(ret->token, "&&", 2) && \
			ft_strncmp(ret->token, "||", 2))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

t_node	*get_next_cmd(t_lst *lst)
{
	t_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && \
			ft_strncmp(ret->token, "|", 2) && \
			ft_strncmp(ret->token, ">", 1) && \
			ft_strncmp(ret->token, "<", 1) && \
			ft_strncmp(ret->token, "&&", 2) && \
			ft_strncmp(ret->token, "||", 2))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

void	move_to_next_cmd(t_lst *lst)
{
	if (!lst->curr->next)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	while (lst->curr && \
			ft_strncmp(lst->curr->token, "|", 2) && \
			ft_strncmp(lst->curr->token, ">", 1) && \
			ft_strncmp(lst->curr->token, "<", 1) && \
			ft_strncmp(lst->curr->token, "&&", 2) && \
			ft_strncmp(lst->curr->token, "||", 2))
		lst->curr = lst->curr->next;
	if (lst->curr)
		lst->curr = lst->curr->next;
}

char 	**get_cmd_args(t_lst *lst)
{
	t_node	*tmp;
	char	**args;
	int		nums;

	nums = 0;
	tmp = lst->curr;
	while (tmp && ft_strncmp(tmp->token, "|", 2) && \
				ft_strncmp(tmp->token, ">", 1) && \
				ft_strncmp(tmp->token, "<", 1) && \
				ft_strncmp(tmp->token, "&&", 2) && \
				ft_strncmp(tmp->token, "||", 2))
	{
		nums++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	args = (char **)ft_calloc(nums + 1, sizeof(char *));
	args[nums--] = NULL;
	while (nums >= 0 && tmp)
	{
		args[nums--] = ft_strdup(tmp->token);
		tmp = tmp->prev;
	}
	return (args);
}

void	run_commands(char **tokens, t_lst *lst, t_env_lst *envlst, char **envp)
{
	int		proc_id;
	int		n_pid;
	
	n_pid = 0;
	push_cmd(lst, tokens);
	init_pipe(lst);
	if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, "<<", 3)) // 시작 전 라인 전체 히어독 한번에 받기 필요.
		redi_heredoc(lst);
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
				else if (get_next_cmd(lst) && !ft_strncmp(get_next_cmd(lst)->prev->token, "<", 1))
					redi_left(lst, envlst, envp);
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
