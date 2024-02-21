/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:48:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/21 12:09:07 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_for_rr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, "|", 2));
		// ft_strncmp(node->token, "&&", 3) && 
		// 	);
		// 	ft_strncmp(node->token, "||", 3) && 
}

t_cmd_node	*get_prev_cmd_rr(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (!is_cmd_for_rr(ret))
		ret = ret->prev;
	while (ret && is_cmd_for_rr(ret))
	{
		if (ret == lst->head)
			return (ret);
		ret = ret->prev;
	}
	return (ret->next);
}

void	redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int			file;
	char 		**args;
	char 		*name;
	char 		*op;
	t_cmd_node	*tmp;

	if (logic_stop(lst))
		exit(g_exit_code);
	tmp = lst->curr;
	while (tmp->next && \
		ft_strncmp(tmp->token, ">>", 3) && \
		ft_strncmp(tmp->token, ">", 2))
		tmp = tmp->next;
	op = tmp->token;
	name = tmp->next->token;
	args = get_cmd_args(lst);
	if (get_prev_cmd_rr(lst) && ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<", 1))
		dup2(lst->curr->pipefd[0], STDIN_FILENO);
	if (!ft_strncmp(op, ">", 2))
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strncmp(op, ">>", 3))
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exit(0);
	dup2(file, STDOUT_FILENO);
	close_pipe(lst);
	close(file);
	if (!builtin_choice(lst, envlst))
	{
		exec_program(envlst, args, envp);
		perror("minishell right redirection");
	}
	exit(0);
}

void	redi_heredoc(t_cmd_lst *lst, char *file_name, char *deli)
{
	int		tmp_file;
	char	*doc_line;
	int		len_deli;
	char	*delim;

	tmp_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	len_deli = ft_strlen(get_next_cmd_for_heredoc(lst->curr)->token);
	delim = ft_strjoin(deli, "\n");
	write(1, "> ", 2);
	doc_line = get_next_line(0);
	while (doc_line && ft_strncmp(doc_line, delim, len_deli + 2))
	{
		write(tmp_file, doc_line, ft_strlen(doc_line));
		free(doc_line);
		write(1, "> ", 2);
		doc_line = get_next_line(0);
	}
	free(doc_line);
	free(delim);
	close(tmp_file);
	g_exit_code = 0;
}

void	reset_written_pipe(t_cmd_lst *lst)
{
	close(lst->curr->pipefd[0]);
	close(lst->curr->pipefd[1]);
	pipe(lst->curr->pipefd);
	dup2(lst->curr->pipefd[0], STDIN_FILENO);
}

void	check_read_auth(t_cmd_lst *lst)
{
	if (access(get_next_cmd_pp(lst)->token, F_OK | R_OK))
	{
		perror("file open error");
		g_exit_code = 1;
		exit(g_exit_code);
	}
}

void	redi_left(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int		file;
	int		ret;
	char	tmp[1024];

	if (envlst && envp) {};
	if (!ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<<", 3))
		file = open(lst->curr->file_heredoc, O_RDONLY, 0666);
	else
	{
		check_read_auth(lst);
		file = open(get_next_cmd_pp(lst)->token, O_RDONLY, 0666);
	}
	reset_written_pipe(lst);
	ret = read(file, tmp, 1024);
	while (ret)
	{
		write(lst->curr->pipefd[1], tmp, ret);
		ret = read(file, tmp, 1024);
	}
	close(file);
	if (!ft_strncmp(get_next_cmd(lst)->prev->token, "<<", 3))
		unlink(lst->curr->file_heredoc);
}

int	is_cmd_for_heredoc(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (ft_strncmp(node->token, ">>", 3) && \
			ft_strncmp(node->token, ">", 2) && \
			ft_strncmp(node->token, "&&", 3) && \
			ft_strncmp(node->token, "<<", 3) && \
			ft_strncmp(node->token, "<", 2) && \
			ft_strncmp(node->token, "||", 3) && \
			ft_strncmp(node->token, "|", 2));
}

t_cmd_node	*get_next_cmd_for_heredoc(t_cmd_node *node)
{
	if (!node->next)
	{
		node = node->next;
		return (NULL);
	}	
	while (node && is_cmd_for_heredoc(node))
		node = node->next;
	if (node)
		node = node->next;
	return (node);
}

void	get_heredoc(t_cmd_lst *lst)
{
	t_cmd_node	*next_cmd;
	t_cmd_node	*name_node;
	char		*get_itoa;
	int			num_heredoc;

	lst->curr = lst->head;
	num_heredoc = 0;
	while (lst->curr)
	{
		name_node = lst->curr;
		get_itoa = ft_itoa(num_heredoc++);
		name_node->file_heredoc = ft_strjoin(".", get_itoa);
		free(get_itoa);
		next_cmd = get_next_cmd_for_heredoc(lst->curr);
		while (next_cmd && !ft_strncmp(next_cmd->prev->token, "<<", 3))
		{
			redi_heredoc(lst, name_node->file_heredoc, next_cmd->token);
			next_cmd = get_next_cmd_for_heredoc(next_cmd);
		}
		move_to_next_cmd(lst);
	}
	lst->curr = lst->head;
}
