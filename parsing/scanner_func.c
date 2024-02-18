/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:23:55 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:18:03 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

char	next_char(t_scanner *src)
{
	char	ch;

	if (!src || !src->line)
		return (0);
	if (src->cur == src->size - 1)
		return (T_EOF);
	src->cur++;
	ch = src->line[src->cur];
	return (ch);
}

char	peek_char(t_scanner *src)
{
	char	ch;
	int		pos;

	if (!src || !src->line)
		return (0);
	pos = src->cur;
	if (++pos >= src->size)
		return (T_EOF);
	ch = src->line[pos];
	return (ch);
}

void	cur_back(t_scanner *src)
{
	if (src->cur <= 0)
		return ;
	src->cur--;
}

void	skip_whitespaces(t_scanner *src)
{
	if (!src || !src->line)
		return ;
	while (peek_char(src) != T_EOF
		&& (peek_char(src) == ' ' || peek_char(src) == '\t')
	)
	{
		next_char(src);
	}
}
