/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:52:26 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:58:19 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_buf	*buf_new(void)
{
	t_buf	*buf;

	buf = ft_calloc2(1, sizeof(t_buf));
	buf->buf = ft_calloc2(1, sizeof(char));
	buf->size = 1;
	return (buf);
}

void	buf_del(t_buf *buf)
{
	free(buf->buf);
	buf->buf = 0;
	buf->size = 0;
	free(buf);
}

void	buf_add_char(t_buf *buf, char c)
{
	if (buf->len + 1 >= buf->size)
	{
		buf->buf = ft_realloc(buf->buf,
				sizeof(char) * buf->size,
				sizeof(char) * buf->size * 2);
		buf->size *= 2;
	}
	buf->buf[buf->len] = c;
	++(buf->len);
}

char	*buf_get_str(t_buf *buf)
{
	char	*str;

	str = ft_strdup(buf->buf);
	if (!str)
		exit_err("MEM Error\n");
	return (str);
}
