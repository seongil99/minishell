/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:05:25 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:18:06 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_scanner	*scanner_new(char *line)
{
	t_scanner	*src;

	if (!line)
		return (NULL);
	src = ft_calloc2(1, sizeof(t_scanner));
	src->line = line;
	src->size = ft_strlen(line);
	src->cur = -1;
	return (src);
}

void	scanner_del(t_scanner *s)
{
	s->cur = 0;
	s->line = 0;
	s->size = 0;
	free(s);
}
