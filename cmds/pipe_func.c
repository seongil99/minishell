/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:29:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/22 17:01:46 by sihkang          ###   ########seoul.kr  */
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

int	is_cmd_pp(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && 
			ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

t_cmd_node	*get_next_cmd_pp(t_cmd_lst *lst)
{
	t_cmd_node	*ret;
	
	ret = lst->curr;
	if (!ret->next)
	{
		ret = ret->next;
		return (NULL);
	}	
	while (ret && is_cmd_pp(ret))
		ret = ret->next;
	if (ret)
		ret = ret->next;
	return (ret);
}

t_cmd_node	*get_prev_cmd_pp(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd_pp(ret))
		ret = ret->prev;
	while (ret && is_cmd_pp(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

char 	**get_cmd_args_pp(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	char	**args;
	int		nums;
	int		size;

	size = 10;
	args = (char **)ft_calloc(size, sizeof(char *));
	args[0] = ft_strdup(lst->curr->token);
	nums = 1;
	tmp = lst->curr->next;
	while (tmp)
	{
		// printf("prev : %s, curr :%s \n", tmp->prev->token, tmp->token);
		if (!ft_strncmp(tmp->token, "<", 1) || \
		!ft_strncmp(tmp->token, ">", 1) || \
		!ft_strncmp(tmp->prev->token, "<", 1) || \
		!ft_strncmp(tmp->prev->token, ">", 1))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!is_cmd_for_move(tmp) || !tmp)
		{
			args[nums] = NULL;
			break;
		}
		if (nums + 1 == size)
		{
			args = ft_realloc(args, size * sizeof(char *), size * sizeof(char *) * 2);
			size *= 2;
		}
		args[nums++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	return (args);
}

void	pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;
	
	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args_pp(lst);
	if (get_next_cmd_after_lr(lst))
		dup2(get_next_cmd_after_lr(lst)->pipefd[1], STDOUT_FILENO);
	close_pipe(lst);
	if (!builtin_choice(lst, envlst))
		exec_program(envlst, args, envp);
	exit(0);
}
