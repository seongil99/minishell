/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:46:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/04 15:39:55 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include <dirent.h>

bool	pattern_match(char *pattern,
			char *target,
			char *backup_pattern,
			char *backup_target);

static char	*get_next_filename(void)
{
	static DIR		*dir;
	struct dirent	*ett;
	char			buf[1024];

	if (!dir)
		dir = opendir(getcwd(buf, 1024));
	ett = readdir(dir);
	if (!ett)
	{
		closedir(dir);
		dir = NULL;
		return (NULL);
	}
	return (ft_strdup(ett->d_name));
}

static int	path_append(t_lst **tknnode, char *filename, char *pattern)
{
	int	cnt;

	cnt = 0;
	if (pattern_match(pattern, filename, NULL, NULL))
	{
		lst_insert_next(tknnode, lst_new(token_new(filename, WORD)));
		*tknnode = (*tknnode)->next;
		cnt++;
	}
	else
		free(filename);
	return (cnt);
}

bool	check_redrt(t_lst *prev, int cnt)
{
	if (prev && (((t_token *)prev->data)->type == DGREAT
			|| ((t_token *)prev->data)->type == DLESS
			|| ((t_token *)prev->data)->type == GREAT
			|| ((t_token *)prev->data)->type == LESS)
		&& cnt >= 2)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", STDERR_FILENO);
		return (true);
	}
	return (false);
}

int	path_expansion(t_lst **head, t_lst *tknnode, t_lst *prev)
{
	t_lst	*temp;
	char	*filename;
	char	*pattern;
	int		cnt;

	if (!tknnode)
		return (1);
	pattern = ((t_token *)tknnode->data)->str;
	temp = tknnode;
	cnt = 0;
	if (!ft_strchr(pattern, '*'))
		return (0);
	while (true)
	{
		filename = get_next_filename();
		if (!filename)
			break ;
		cnt += path_append(&tknnode, filename, pattern);
	}
	if (check_redrt(prev, cnt))
		return (1);
	if (cnt)
		lst_del(head, temp, token_del);
	return (0);
}
