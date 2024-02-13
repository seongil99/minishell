/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/13 12:06:46 by sihkang          ###   ########seoul.kr  */
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

void	redi_right(t_lst *lst, char **envp)
{
	int	file;
	char *args[2];

	args[0] = "for test";
	args[1] = NULL;

	close_pipe(lst);
	if (!ft_strncmp(lst->curr->next->token, ">", 2))
		file = open(lst->curr->next->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file = open(lst->curr->next->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(file, STDOUT_FILENO);
	close(file);
	execve(lst->curr->token, args, envp);
	perror("minishell right redirection");
	exit(0);
}

void	redi_heredoc(t_lst *lst, char **envp)
{
	int		tmp_file;
	char	*doc_line;
	int		len_deli;
	char	tmp[1025];
	int		ret;
	char 	*args[2];
	int		pid;
	
	args[0] = "heredoc";
	args[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		tmp_file = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		len_deli = ft_strlen(lst->curr->next->next->token) + 1;
		doc_line = get_next_line(0);
		while (ft_strncmp(doc_line, lst->curr->next->next->token, len_deli))
		{
			write(tmp_file, doc_line, ft_strlen(doc_line));
			free(doc_line);
			doc_line = get_next_line(0);
		}
		free(doc_line);
		close(tmp_file);
		tmp_file = open(".tmp", O_RDONLY, 0666);
		ret = read(tmp_file, tmp, 1024);
		while (ret)
		{
			write(lst->curr->pipefd[0], tmp, ret);
			ret = read(tmp_file, tmp, 1024);
		}
		close_pipe(lst);
		close(tmp_file);
		execve(lst->curr->token, args, envp);
		perror("minishell heredoc");
		exit(0);
	}
}

void	redi_left(t_lst *lst, char **envp)
{
	int		file;
	char 	*args[2];
	char	tmp[1025];
	int		ret;
	
	args[0] = "left redirection test";
	args[1] = NULL;
	dup2(lst->curr->pipefd[0], STDIN_FILENO);
	file = open(lst->curr->next->next->token, O_RDONLY, 0666);
	ret = read(file, tmp, 1024);
	while (ret)
	{
		write(lst->curr->pipefd[1], tmp, ret);
		ret = read(file, tmp, 1024);
	}
	close(file);
	close_pipe(lst);
	execve(lst->curr->token, args, envp);
	perror("minishell left redirection");
	exit(0);
}

// void	pipe_exec(t_lst *lst, char *envp[])
// {
// 	char	**args;

// 	args = get_args(lst);
// 	if (lst->curr != lst->tail)
// 		dup2(lst->curr->pipefd[1], STDOUT_FILENO);
// 	if (lst->curr != lst->head)
// 		dup2(lst->curr->prev->prev->pipefd[0], STDIN_FILENO);
// 	close_pipe(lst);
// 	execve(lst->curr->token, args, envp);
// 	perror("minishell pipe line");
// }



void	run_commands(char **tokens, t_lst *lst, char **envp)
{
	int		proc_id;
	char	*args[2];

	args[0] = "asdf1";
	args[1] = NULL;
	push_cmd(lst, tokens);
	init_pipe(lst);
	while (lst->curr)
	{
		if (ft_strncmp(lst->curr->token, "|", 2)) // cmd 라면,
		{
			proc_id = fork();
			if (proc_id == 0)
			{
				if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, "|", 2)) 
				{
					if (lst->curr != lst->tail)
						dup2(lst->curr->pipefd[1], STDOUT_FILENO);
					if (lst->curr != lst->head)
						dup2(lst->curr->prev->prev->pipefd[0], STDIN_FILENO);
					close_pipe(lst);
					execve(lst->curr->token, args, envp);
					perror("minishell pipe line");
				}
				else if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, ">", 1))
					redi_right(lst, envp);
				else if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, "<", 1))
					redi_left(lst, envp);
				else
				{
					if (lst->curr != lst->head)
						dup2(lst->curr->prev->prev->pipefd[0], STDIN_FILENO);
					close_pipe(lst);
					if (execve(lst->curr->token, args, envp))
					{
						perror("last cmd");
						exit(0);
					}
				}
			}
		}
		if (lst->curr != lst->tail && !ft_strncmp(lst->curr->next->token, ">", 1))
		{
			lst->curr = lst->curr->next;
			lst->curr = lst->curr->next;
		}
		lst->curr = lst->curr->next;
	}
	close_pipe(lst);
	while (lst->nums--)
		wait(0);
}
