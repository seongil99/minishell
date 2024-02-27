/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:48:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 09:56:53 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	open_file_readonly(t_cmd_lst *lst)
{
	if (get_next_cmd_pp(lst)->prev->type == DLESS)
		return (open(lst->curr->file_heredoc, O_RDONLY, 0666));
	else
	{
		check_read_auth(lst);
		return (open(get_next_cmd_pp(lst)->token, O_RDONLY, 0666));
	}
}

void	redi_left(t_cmd_lst *lst)
{
	int		file;
	int		ret;
	char	tmp[1024];

	if (lst->curr->type != WORD)
		return ;
	reset_written_pipe(lst);
	file = open_file_readonly(lst);
	ret = read(file, tmp, 1024);
	while (ret)
	{
		if (lst->curr->type == WORD)
			write(lst->curr->pipefd[1], tmp, ret);
		else
			write(0, tmp, ret);
		ret = read(file, tmp, 1024);
	}
	close(file);
	if (!ft_strncmp(get_next_cmd_pp(lst)->prev->token, "<<", 3))
		unlink(lst->curr->file_heredoc);
}
