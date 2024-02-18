/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:46:38 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 19:11:52 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static void	double_quote(t_buf *buf, char c, int *flag)
{
	if (c == '\"')
		*flag = NO_QUOTE;
	else
		buf_add_char(buf, c);
}

static void	single_quote(t_buf *buf, char c, int *flag)
{
	if (c == '\'')
		*flag = NO_QUOTE;
	else
		buf_add_char(buf, c);
}

static void	no_quote(t_buf *buf, char c, int *flag)
{
	if (c == '\"')
		*flag = DQUOTE;
	else if (c == '\'')
		*flag = SQUOTE;
	else
		buf_add_char(buf, c);
}

static void	insert_char(t_buf *buf, char c, int *flag)
{
	if (*flag == NO_QUOTE)
		no_quote(buf, c, flag);
	else if (*flag == SQUOTE)
		single_quote(buf, c, flag);
	else if (*flag == DQUOTE)
		double_quote(buf, c, flag);
}

char	*quote_removal(char *str)
{
	int		flag;
	t_buf	*buf;
	char	*ret;

	if (!str)
		return (NULL);
	flag = NO_QUOTE;
	buf = buf_new();
	while (*str)
	{
		insert_char(buf, *str, &flag);
		str++;
	}
	ret = buf_get_str(buf);
	buf_del(buf);
	return (ret);
}
