/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:22:19 by seonyoon          #+#    #+#             */
/*   Updated: 2023/10/20 16:43:02 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	i;
	size_t	mul;

	if (!count || !size)
		return (malloc(0));
	mul = count * size;
	if (mul / count != size)
		return (0);
	ret = (char *)malloc(mul);
	if (!ret)
		return (0);
	i = 0;
	while (i < mul)
	{
		ret[i] = 0;
		i++;
	}
	return ((void *)ret);
}
