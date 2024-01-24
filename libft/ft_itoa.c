/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:52:46 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/15 13:12:40 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*rev(char *s, size_t len)
{
	size_t	i;
	char	t;

	i = 0;
	while (i < len / 2)
	{
		t = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = t;
		i++;
	}
	return (s);
}

static size_t	num_len(int n)
{
	size_t	ret;

	ret = 0;
	if (n < 0)
		ret++;
	while (n / 10)
	{
		ret++;
		n /= 10;
	}
	return (ret + 1);
}

char	*ft_itoa(int n)
{
	char	*ret;
	char	i;
	size_t	len;

	ret = (char *)malloc(sizeof(char) * (num_len(n) + 1));
	if (!ret)
		return (0);
	len = 0;
	while (n / 10)
	{
		i = n % 10;
		if (i < 0)
			i *= -1;
		ret[len++] = i + '0';
		n /= 10;
	}
	if (n < 0)
	{
		ret[len++] = n * -1 + '0';
		ret[len++] = '-';
	}
	else
		ret[len++] = n + '0';
	ret[len] = '\0';
	return (rev(ret, len));
}
