/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:37:16 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/10 17:02:08 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp(const char *haystack, const char *needle, size_t n)
{
	size_t	i;

	i = 0;
	while (needle[i] && haystack[i] && i < n)
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	if (i == n)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;

	if (!*needle)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	i = 0;
	n_len = ft_strlen(needle);
	while (*haystack && i + n_len <= len)
	{
		if (*(haystack + i) == *needle)
			if (cmp(haystack + i, needle, n_len))
				return ((char *)(haystack + i));
		i++;
	}
	return (0);
}
