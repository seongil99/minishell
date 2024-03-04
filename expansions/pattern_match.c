/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:35:27 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/04 15:39:59 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

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

bool	pattern_match(
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
