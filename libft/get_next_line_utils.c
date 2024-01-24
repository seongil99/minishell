/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:11 by seonyoon          #+#    #+#             */
/*   Updated: 2023/12/22 18:25:36 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*ft_gnllstnew(int fd)
{
	t_gnl_list	*node;

	node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!node)
	{
		return (0);
	}
	node->buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!node->buf)
	{
		free(node);
		return (0);
	}
	node->next = 0;
	node->prev = 0;
	node->fd = fd;
	node->size = 0;
	node->len = 0;
	node->lb = 0;
	node->err = 0;
	return (node);
}

t_gnl_list	*get_node(t_gnl_list **lst, int fd)
{
	t_gnl_list	*node;
	t_gnl_list	*list;

	list = *lst;
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	node = ft_gnllstnew(fd);
	if (!node)
		return (0);
	if (!*lst)
	{
		*lst = node;
		return (node);
	}
	node->next = *lst;
	(*lst)->prev = node;
	*lst = node;
	return (node);
}

char	*realloc_str(t_gnl_list *node, char *str, size_t sz)
{
	char	*temp;
	size_t	i;

	if (!str)
		return (0);
	temp = (char *)ft_calloc((sz + 1), sizeof(char));
	if (!temp)
	{
		free(str);
		return (0);
	}
	i = 0;
	while (i < sz && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	node->size = sz;
	free(str);
	str = temp;
	return (str);
}
