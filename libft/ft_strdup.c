/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:38:42 by seonyoon          #+#    #+#             */
/*   Updated: 2023/10/09 16:44:58 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	s1_len;
	char	*ret;

	s1_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!ret)
	{
		errno = ENOMEM;
		return (0);
	}
	i = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
