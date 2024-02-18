/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:25:47 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/16 10:32:47 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	head;
	t_list_gnl			*nodes[2];
	char				*ret;

	if (fd < 0 || fd == 2)
		return (0);
	ret = ft_find_next_line(&head, fd);
	if (ret == 0 && head.next)
	{
		nodes[0] = &head;
		nodes[1] = nodes[0]->next;
		while (nodes[1]->buf_info[0] != fd)
		{
			nodes[0] = nodes[1];
			nodes[1] = nodes[1]->next;
			if (!nodes[1])
				return (0);
		}
		nodes[0]->next = nodes[1]->next;
		free(nodes[1]->buf_info);
		free(nodes[1]->buf);
		free(nodes[1]);
	}
	return (ret);
}

t_list_gnl	*ft_find_node(t_list_gnl *head, int fd)
{
	t_list_gnl	*node;

	node = head;
	while (node->next)
	{
		if ((int)node->next->buf_info[0] == fd)
			return (node->next);
		node = node->next;
	}
	node->next = (t_list_gnl *)ft_calloc2(sizeof(t_list_gnl), 1);
	if (!node->next)
		return (0);
	node->next->buf = (char *)ft_calloc2(sizeof(char), (BUFFER_SIZE + 1));
	node->next->buf_info = (long long *)ft_calloc2(sizeof(long long), 3);
	if (!(node->next->buf_info) || !(node->next->buf))
	{
		free(node->next->buf);
		free(node->next->buf_info);
		free(node->next);
		node->next = 0;
		return (0);
	}
	node->next->buf_info[0] = fd;
	return (node->next);
}

char	*ft_find_next_line(t_list_gnl *head, int fd)
{
	char		*str;
	size_t		str_index;
	size_t		str_max;
	t_list_gnl	*node;

	str_index = 0;
	str_max = BUFFER_SIZE;
	str = (char *)ft_calloc2(sizeof(char), (BUFFER_SIZE + 1));
	node = (ft_find_node(head, fd));
	if (!node)
	{
		free(str);
		return (0);
	}
	str = ft_make_str(node, str, str_index, str_max);
	if (str == 0 || str[0] == '\0' || node->buf_info[2] == -1)
	{
		free(str);
		str = 0;
	}
	return (str);
}

char	*ft_make_str(t_list_gnl *node, char *str, \
					size_t str_index, size_t str_max)
{
	while (1)
	{
		if (node->buf_info[1] == node->buf_info[2])
		{
			node->buf_info[1] = 0;
			node->buf_info[2] = read(node->buf_info[0], node->buf, BUFFER_SIZE);
			if (node->buf_info[2] <= 0)
				return (ft_realloc_gnl(str, str_index, &str_max, 1));
		}
		while (node->buf_info[1] < node->buf_info[2])
		{
			str[str_index] = node->buf[node->buf_info[1]++];
			if (str[str_index++] == '\n')
				return (ft_realloc_gnl(str, str_index, &str_max, 1));
			else if (str_index == str_max)
			{
				str = ft_realloc_gnl(str, str_index, &str_max, 0);
				if (!str)
					return (0);
			}
		}
		if (node->buf_info[2] < BUFFER_SIZE)
			return (ft_realloc_gnl(str, str_index, &str_max, 1));
	}
}

char	*ft_realloc_gnl(char *str, size_t str_index, \
						size_t	*str_max, int option)
{
	char	*newstr;
	size_t	len;
	size_t	index;

	index = 0;
	if (option == 0)
		len = (str_index + BUFFER_SIZE) * 2;
	else
		len = str_index;
	newstr = (char *)ft_calloc2(sizeof(char), (len + 1));
	if (newstr)
	{
		while (index < str_index)
		{
			newstr[index] = str[index];
			index++;
		}
		newstr[index] = 0;
	}
	*str_max = len;
	free(str);
	str = 0;
	return (newstr);
}
