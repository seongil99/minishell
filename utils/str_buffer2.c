/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_buffer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:10:22 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 13:40:54 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_utils.h"

void	buf_remove_char(t_buf *buf, int index)
{
	while (index < buf->size - 1)
	{
		buf->buf[index] = buf->buf[index + 1];
		++index;
	}
	buf->len--;
}
