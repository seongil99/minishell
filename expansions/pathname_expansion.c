/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:46:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 14:37:54 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include <dirent.h>

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

static bool	match_with_star(
	char **pattern,
	char **target,
	char **backup_pattern,
	char **backup_target
	)
{
	if (**pattern == '*')
	{
		while (**pattern == '*')
			(*pattern)++;
		if (!**pattern)
			return (true);
		*backup_pattern = *pattern;
		*backup_target = *target + 1;
		return (false);
	}
	return (false);
}

static bool	pattern_match(
	char *pattern,
	char *target,
	char *backup_pattern,
	char *backup_target
	)
{
	if (*target == '.' && *pattern != '.')
		return (false);
	while (*target)
	{
		if (match_with_star(&pattern, &target, &backup_pattern, &backup_target))
			return (true);
		else if (*pattern == *target)
		{
			pattern++;
			target++;
		}
		else
		{
			if (backup_pattern)
			{
				pattern = backup_pattern;
				target = backup_target++;
			}
			else
				return (false);
		}
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
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

void	path_expansion(t_lst **head, t_lst *tknnode)
{
	t_lst	*temp;
	char	*filename;
	char	*pattern;
	int		cnt;

	if (!tknnode)
		return ;
	pattern = ((t_token *)tknnode->data)->str;
	temp = tknnode;
	cnt = 0;
	if (!ft_strchr(pattern, '*'))
		return ;
	while (true)
	{
		filename = get_next_filename();
		if (!filename)
			break ;
		cnt += path_append(&tknnode, filename, pattern);
	}
	if (cnt)
		lst_del(head, temp, token_del);
}
