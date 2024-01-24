/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:48:07 by seonyoon          #+#    #+#             */
/*   Updated: 2023/10/09 18:31:39 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (!dst && !src)
		return (0);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (dst < src && len != 0)
	{
		i = 0;
		while (i < len)
		{
			*(dst_ptr + i) = *(src_ptr + i);
			i++;
		}
	}
	else if (dst > src && len != 0)
	{
		i = len;
		while (i-- != 0)
			*(dst_ptr + i) = *(src_ptr + i);
	}
	return (dst);
}
