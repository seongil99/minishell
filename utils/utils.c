/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:47:24 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/22 09:21:56 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mini_utils.h"

void	exit_err(char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(1);
}

void	mini_assert(bool condition, char *msg)
{
	if (condition)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	exit(1);
}

void	*ft_realloc(void *ptr, size_t ptrsize, size_t tosize)
{
	unsigned char	*p;
	unsigned char	*ret;
	size_t			i;

	p = ptr;
	ret = ft_calloc2(tosize, sizeof(unsigned char));
	i = 0;
	while (i < ptrsize)
	{
		ret[i] = p[i];
		i++;
	}
	p = 0;
	free(ptr);
	return ((void *)ret);
}
