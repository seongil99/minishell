/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:34:58 by seonyoon          #+#    #+#             */
/*   Updated: 2023/10/20 14:08:32 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*f_s;

	f_s = (char *)s;
	cc = (char)c;
	while (*s)
		s++;
	while (s != f_s)
	{
		if (*s == cc)
			break ;
		s--;
	}
	if (*s == cc)
		return ((char *)s);
	return (0);
}
