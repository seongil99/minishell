/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:19:16 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/05 10:35:32 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_parents_action(pid_t id, char *delim, int tmp_file)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(id, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	free(delim);
	close(tmp_file);
}

void	heredoc_child_action(t_cmd_lst *lst, t_env_lst *envlst, \
							char *delim, int tmp_file)
{
	char	*doc_line;
	int		len_deli;
	char	*temp;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	len_deli = ft_strlen(get_next_cmd_for_heredoc(lst->curr)->token);
	write(1, "> ", 2);
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

int	redi_heredoc(t_cmd_lst *lst, t_env_lst *envlst, char *file_name, char *deli)
{
	int		tmp_file;
	char	*delim;
	pid_t	id;

	tmp_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	delim = ft_strjoin(deli, "\n");
	id = fork2();
	if (id == 0)
		heredoc_child_action(lst, envlst, delim, tmp_file);
	else
		heredoc_parents_action(id, delim, tmp_file);
	return (g_exit_code);
}

void	get_heredoc(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_cmd_node	*nxtcmd;
	t_cmd_node	*tg;
	char		*get_itoa;
	int			num_heredoc;

	num_heredoc = 0;
	g_exit_code = 0;
	while (lst->curr)
	{
		while (lst->curr->type == LPAR || lst->curr->type == RPAR)
			lst->curr = lst->curr->next;
		tg = lst->curr;
		get_itoa = ft_itoa(num_heredoc++);
		tg->file_heredoc = ft_strjoin(".", get_itoa);
		free(get_itoa);
		nxtcmd = get_next_cmd_for_heredoc(lst->curr);
		while (nxtcmd)
		{
			if (nxtcmd->prev->type == DLESS)
				if (redi_heredoc(lst, envlst, tg->file_heredoc, nxtcmd->token))
					break ;
			nxtcmd = get_next_cmd_for_heredoc(nxtcmd);
		}
		move_to_next_cmd_heredoc(lst);
	}
}
