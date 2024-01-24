/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:03 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/10 17:02:16 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_included(char c, char const *set)
{
	while (*set)
		if (*(set++) == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (!s1)
		return (0);
	if (!set && !*set)
		return (ft_strdup(s1));
	while (*s1 && is_included(*s1, set))
		s1++;
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (!is_included(s1[i], set))
			len = i + 1;
		i++;
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
