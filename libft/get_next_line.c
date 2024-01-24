/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:44:49 by seonyoon          #+#    #+#             */
/*   Updated: 2023/12/22 16:50:18 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	del_node(t_gnl_list **lst, t_gnl_list *node)
{
	if (*lst == node)
		*lst = node->next;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	free(node->buf);
	free(node);
}

char	*cpy_buf(t_gnl_list *node, char **line, size_t sz)
{
	size_t	i;

	if (!*line)
		return (0);
	if (node->size < node->len + BUFFER_SIZE + 1)
	{
		*line = realloc_str(node, *line, node->size * 2);
		if (!*line)
			return (0);
	}
	i = 0;
	while (node->buf[i] && i < sz)
	{
		(*line)[node->len + i] = node->buf[i];
		if (!node->lb && node->buf[i] == '\n')
			node->lb = node->len + i + 1;
		i++;
	}
	(*line)[node->len + i] = '\0';
	if (node->lb)
		ft_memmove(node->buf, node->buf + node->lb - node->len,
			BUFFER_SIZE + 1 - (node->lb - node->len));
	node->len += i;
	return (*line);
}

ssize_t	read_line(t_gnl_list *node, char **line)
{
	ssize_t	sz;

	sz = read(node->fd, node->buf, BUFFER_SIZE);
	if (sz < 0)
		node->err = 1;
	if (sz <= 0)
		return (0);
	node->buf[sz] = '\0';
	*line = cpy_buf(node, line, sz);
	if (!*line)
		return (0);
	return (sz);
}

char	*get_one_line(t_gnl_list *node, char **line)
{
	*line = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	node->size = BUFFER_SIZE + 1;
	*line = cpy_buf(node, line, BUFFER_SIZE);
	if (!*line)
		return (0);
	while (!node->lb && read_line(node, line) == BUFFER_SIZE)
		;
	if (!node->lb)
	{
		node->lb = node->len;
		node->buf[0] = '\0';
	}
	*line = realloc_str(node, *line, node->lb);
	node->len = 0;
	node->lb = 0;
	if (!*line)
		return (0);
	if ((*line)[0] == '\0' || node->err)
	{
		free(*line);
		return (0);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*lst;
	t_gnl_list			*node;
	char				*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	node = get_node(&lst, fd);
	if (!node)
		return (0);
	line = get_one_line(node, &line);
	if (!line || node->err)
	{
		del_node(&lst, node);
		return (0);
	}
	return (line);
}
