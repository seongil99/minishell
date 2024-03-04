/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:24:07 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/27 20:05:10 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*get_home_dir(t_env_lst *envlst)
{
	char		*home_dir;

	home_dir = envlst->home;
	return (home_dir);
}

void	replace_str(char **dist, char *new_str)
{
	free(*(dist));
	*dist = new_str;
}

void	set_quote_flag(int *flag, char c)
{
	if (*flag == NO_QUOTE)
	{
		if (c == '\"')
			*flag = DQUOTE;
		else if (c == '\'')
			*flag = SQUOTE;
	}
	else if (*flag == SQUOTE)
	{
		if (c == '\'')
			*flag = NO_QUOTE;
	}
	else if (*flag == DQUOTE)
	{
		if (c == '\"')
			*flag = NO_QUOTE;
	}
}
