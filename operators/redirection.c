/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:48:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 12:10:35 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (lst->curr != lst->head)
		dup2(get_prev_cmd(lst)->pipefd[0], STDIN_FILENO);
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
		exec_program(envlst, args, envp);
		// execve(lst->curr->token, args, envp);
	perror("minishell right redirection");
	exit(0);
}

void	redi_heredoc(t_cmd_lst *lst, char *file_name)
{
	int		tmp_file;
	char	*doc_line;
	int		len_deli;
	char	*deli;

	tmp_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	len_deli = ft_strlen(get_next_cmd(lst)->token);
	deli = ft_strjoin(get_next_cmd(lst)->token, "\n");
	write(1, "> ", 2);
	doc_line = get_next_line(0);
	while (ft_strncmp(doc_line, deli, len_deli + 2))
	{
		write(tmp_file, doc_line, ft_strlen(doc_line));
		free(doc_line);
		write(1, "> ", 2);
		doc_line = get_next_line(0);
	}
	free(doc_line);
	free(deli);
	close(tmp_file);
}

void	redi_left(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int		file;
	int		ret;
	char	tmp[1025];

	if (envlst && envp) {};
	dup2(lst->curr->pipefd[0], STDIN_FILENO);
	if (!ft_strncmp(get_next_cmd(lst)->prev->token, "<<", 3))
		file = open(lst->curr->file_heredoc, O_RDONLY, 0666);
	else
		file = open(get_next_cmd(lst)->token, O_RDONLY, 0666);
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

void	get_heredoc(t_cmd_lst *lst)
{
	int			num_heredoc;
	char		*get_itoa;

	num_heredoc = 0;
	lst->curr = lst->head;
	while (lst->curr)
	{
		if (get_next_cmd(lst) && !ft_strncmp(get_next_cmd(lst)->prev->token, "<<", 3))
		{
			get_itoa = ft_itoa(num_heredoc);
			lst->curr->file_heredoc = ft_strjoin(".", get_itoa);
			free(get_itoa);
			redi_heredoc(lst, lst->curr->file_heredoc);
			num_heredoc++;
		}
		lst->curr = get_next_cmd(lst);
	}
	lst->curr = lst->head;
}
