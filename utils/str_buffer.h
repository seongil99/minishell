/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_buffer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:39:11 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 13:14:39 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_BUFFER_H
# define STR_BUFFER_H

typedef struct s_buf
{
	char	*buf;
	int		len;
	int		size;
}	t_buf;

t_buf	*buf_new(void);
void	buf_del(t_buf *buf);
void	buf_add_char(t_buf *buf, char c);
void	buf_add_str(t_buf *buf, char *str);
char	*buf_get_str(t_buf *buf);
void	buf_remove_char(t_buf *buf, int index);

#endif
