/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:24:07 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/05 12:36:11 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "../libft/libft.h"

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

void	set_quote_flag(int *flag, char c, char *str)
{
	if (*flag == NO_QUOTE)
	{
		if (c == '\"' && ft_strchr(str + 1, '\"'))
			*flag = DQUOTE;
		else if (c == '\'' && ft_strchr(str + 1, '\''))
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
