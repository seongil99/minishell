/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:00 by seonyoon          #+#    #+#             */
/*   Updated: 2023/12/22 18:25:51 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include "libft.h"

typedef struct s_gnl_list
{
	char				*buf;
	int					fd;
	int					err;
	size_t				lb;
	size_t				size;
	size_t				len;
	struct s_gnl_list	*next;
	struct s_gnl_list	*prev;
}	t_gnl_list;

char		*get_next_line(int fd);
t_gnl_list	*ft_gnllstnew(int fd);
t_gnl_list	*get_node(t_gnl_list **lst, int fd);
char		*realloc_str(t_gnl_list *node, char *str, size_t sz);

#endif
