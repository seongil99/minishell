/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:48:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/14 09:43:21 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	redi_right(t_lst *lst, t_env_lst *envlst, char **envp)
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
	if (!builtin_choice(lst, envlst))
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

void	redi_left(t_lst *lst, t_env_lst *envlst, char **envp)
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
	if (!builtin_choice(lst, envlst))
		execve(lst->curr->token, args, envp);
	perror("minishell left redirection");
	exit(0);
}
