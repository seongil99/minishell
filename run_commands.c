/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/18 19:44:35 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_cmd(t_cmd_lst *lst, char **tokens)
{
	t_cmd_node	*new;
	int		i;

	i = 0;
	while (tokens[i])
	{
		new = (t_cmd_node *)ft_calloc2(sizeof(t_cmd_node), 1);
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

int is_next_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;

	tmp = lst->curr;
	while (tmp && is_cmd(tmp))
		tmp = tmp->next;
	while (tmp && !is_cmd(tmp))
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	return (1);
}

void	pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;

	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args(lst);
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

int	is_cmd(t_cmd_node *node)
{
	return (ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "(", 2) && \
			ft_strncmp(node->token, ")", 2) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

void	clear_lst(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	t_cmd_node	*del;

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

t_cmd_node	*get_prev_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	ret = lst->curr->prev;
	while (!is_cmd(ret))
		ret = ret->prev;
	while (ret && is_cmd(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	if (!ft_strncmp(ret->token, "<", 2) || \
	!ft_strncmp(ret->token, "<<", 3))
		return (get_prev_cmd(lst));
	return (ret->next);
}

t_cmd_node	*get_next_cmd(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

void	move_to_next_cmd(t_cmd_lst *lst)
{
	if (!lst->curr)
		return ;
	if (!lst->curr->next)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	while (lst->curr && is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
	while (lst->curr && !is_cmd(lst->curr))
	{
		if (!ft_strncmp(lst->curr->token, "(", 2))
			exec_subshell(lst);
		else if (!ft_strncmp(lst->curr->token, ")", 2))
			exit(g_exit_code);
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
}

char 	**get_cmd_args(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	char	**args;
	int		nums;

	nums = 0;
	tmp = lst->curr;
	while (tmp && is_cmd(tmp))
	{
		nums++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!is_cmd(tmp))
		tmp = tmp->prev;
	args = (char **)ft_calloc(nums + 1, sizeof(char *));
	args[nums--] = NULL;
	while (nums >= 0 && tmp)
	{
		args[nums--] = ft_strdup(tmp->token);
		tmp = tmp->prev;
	}
	return (args);
}

void	get_heredoc(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	int			num_heredoc;
	char		*get_itoa;

	num_heredoc = 0;
	tmp = lst->head;
	while (tmp)
	{
		if (tmp != lst->tail && \
		!ft_strncmp(get_next_cmd(lst)->prev->token, "<<", 3) && \
		is_cmd(tmp))
		{
			get_itoa = ft_itoa(num_heredoc);
			tmp->file_heredoc = ft_strjoin(".", get_itoa);
			free(get_itoa);
			redi_heredoc(lst, tmp->file_heredoc);
			num_heredoc++;
		}
		tmp = tmp->next;
	}
}

void	run_commands(char **tokens, t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int		proc_id;
	int		n_pid;
	
	n_pid = 0;
	push_cmd(lst, tokens);
	init_pipe(lst);
	get_heredoc(lst);
	while (lst->curr)
	{
		if (lst->curr != lst->tail && \
			(!ft_strncmp(lst->curr->next->token, "&&", 3) || \
			!ft_strncmp(lst->curr->next->token, "||", 3)))
			logic_control(lst, envlst, envp);
		else if (lst->curr->prev && !ft_strncmp(lst->curr->prev->token, "<", 1))
			lst->curr = lst->curr->next;
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
