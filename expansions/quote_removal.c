/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:46:38 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 13:42:17 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static void	double_quote(t_buf *buf, char c, t_quote_info *data)
{
	if (c == '\"')
	{
		data->flag = NO_QUOTE;
		buf_remove_char(buf, data->idx);
	}
	else
		buf_add_char(buf, c);
}

static void	single_quote(t_buf *buf, char c, t_quote_info *data)
{
	if (c == '\'')
	{
		data->flag = NO_QUOTE;
		buf_remove_char(buf, data->idx);
	}
	else
		buf_add_char(buf, c);
}

static void	no_quote(t_buf *buf, char c, t_quote_info *data)
{
	if (c == '\"')
	{
		data->flag = DQUOTE;
		buf_add_char(buf, c);
		data->idx = buf->len - 1;
	}
	else if (c == '\'')
	{
		data->flag = SQUOTE;
		buf_add_char(buf, c);
		data->idx = buf->len - 1;
	}
	else
		buf_add_char(buf, c);
}

static void	insert_char(t_buf *buf, char c, t_quote_info *data)
{
	if (data->flag == NO_QUOTE)
		no_quote(buf, c, data);
	else if (data->flag == SQUOTE)
		single_quote(buf, c, data);
	else if (data->flag == DQUOTE)
		double_quote(buf, c, data);
}

char	*quote_removal(char *str)
{
	t_quote_info	data;
	t_buf			*buf;
	char			*ret;
	int				i;

	if (!str)
		return (NULL);
	data.flag = NO_QUOTE;
	ft_bzero(&data, sizeof(t_quote_info));
	buf = buf_new();
	i = 0;
	while (str[i])
	{
		insert_char(buf, str[i], &data);
		i++;
	}
	ret = buf_get_str(buf);
	buf_del(buf);
	return (ret);
}
