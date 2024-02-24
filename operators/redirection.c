/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:48:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/24 17:44:22 by sihkang          ###   ########seoul.kr  */
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
	if (!ft_strncmp(ret->token, "&&", 3) || !ft_strncmp(ret->token, "||", 3))
		return (NULL);
	while (ret && is_cmd_for_rr(ret))
	{
		if (ret == lst->head && ret->type == WORD)
			return (ret);
		else if (ret->type != WORD)
			return (NULL);
		ret = ret->prev;
	}
	return (ret->next);
}

// t_cmd_node	*new_get_prev_cmd(t_cmd_lst *lst)
// {
// 	t_cmd_node	*ret;

// 	if (lst->curr == lst->head)
// 		return (NULL);
// 	ret = lst->curr->prev;
// 	while (ret && ret->type != WORD)
// 	{
// 		if (ret->type == AND_IF || ret->type == OR_IF)
// 			return (NULL);
// 		ret = ret->prev;
// 	}
// 	while (ret && ret->type == WORD)
// 	{
// 		if (ret == lst->head)
// 			return (ret);
// 		ret = ret->prev;
// 	}
// 	if (!ret)
// 		return (NULL);
// 	else
// 		return (ret->next);	
// }

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
	args = get_cmd_args_pp(lst);
	if (get_prev_cmd_rr(lst) && ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<", 1))
		dup2(lst->curr->pipefd[0], STDIN_FILENO);
	if (!ft_strncmp(op, ">", 2))
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (!ft_strncmp(op, ">>", 3))
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		exit(g_exit_code);
	dup2(file, STDOUT_FILENO);
	close_pipe(lst);
	close(file);
	if (!builtin_choice(lst, envlst))
	{
		exec_program(envlst, args, envp);
		perror("minishell right redirection");
	}
	exit(g_exit_code);
}

int	redi_heredoc(t_cmd_lst *lst, t_env_lst *envlst, char *file_name, char *deli)
{
	int		tmp_file;
	char	*doc_line;
	int		len_deli;
	char	*delim;
	char	*temp;
	pid_t	id;

	tmp_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	len_deli = ft_strlen(get_next_cmd_for_heredoc(lst->curr)->token);
	delim = ft_strjoin(deli, "\n");
	write(1, "> ", 2);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, sigint_handler_child);
		signal(SIGQUIT, SIG_IGN);
		doc_line = get_next_line(0);
		while (doc_line && ft_strncmp(doc_line, delim, len_deli + 2))
		{
			temp = param_expansion(doc_line, envlst, true);
			write(tmp_file, temp, ft_strlen(temp));
			free(doc_line);
			free(temp);
			write(1, "> ", 2);
			doc_line = get_next_line(0);
		}
		free(doc_line);
		free(delim);
		close(tmp_file);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(id, &g_exit_code, 0);
	}
	free(delim);
	close(tmp_file);
	return (g_exit_code);
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
		exit(1);
	}
}

void	redi_left(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int		file;
	int		ret;
	char	tmp[1024];

	if (envlst && envp) {};
	reset_written_pipe(lst);
	if (!ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<<", 3))
		file = open(lst->curr->file_heredoc, O_RDONLY, 0666);
	else
	{
		check_read_auth(lst);
		file = open(get_next_cmd_pp(lst)->token, O_RDONLY, 0666);
	}
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

void	move_to_next_cmd_heredoc(t_cmd_lst *lst)
{
	if (!lst->curr)
		return ;
	if (!lst->curr->next)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	while (lst->curr && is_cmd_for_move(lst->curr))
	{
		if (lst->curr)
			lst->curr = lst->curr->next;
	}
	if (lst->curr && !is_cmd(lst->curr))
		if (lst->curr)
			lst->curr = lst->curr->next;
}

void	get_heredoc(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_cmd_node	*next_cmd;
	t_cmd_node	*name_node;
	char		*get_itoa;
	int			num_heredoc;

	lst->curr = lst->head;
	num_heredoc = 0;
	g_exit_code = 0;
	while (lst->curr)
	{
		name_node = lst->curr;
		get_itoa = ft_itoa(num_heredoc++);
		name_node->file_heredoc = ft_strjoin(".", get_itoa);
		free(get_itoa);
		next_cmd = get_next_cmd_for_heredoc(lst->curr);
		while (next_cmd && !ft_strncmp(next_cmd->prev->token, "<<", 3))
		{
			if (redi_heredoc(lst, envlst, name_node->file_heredoc, next_cmd->token))
				break ;
			next_cmd = get_next_cmd_for_heredoc(next_cmd);
		}
		move_to_next_cmd_heredoc(lst);
	}
	lst->curr = lst->head;
}
