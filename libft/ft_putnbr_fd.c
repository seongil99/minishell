/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:29:49 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/10 17:01:47 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*rev_str(char *s, size_t len)
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

void	ft_putnbr_fd(int n, int fd)
{
	char	num[20];
	char	i;
	size_t	len;

	len = 0;
	while (n / 10)
	{
		i = n % 10;
		if (i < 0)
			i *= -1;
		num[len++] = i + '0';
		n /= 10;
	}
	if (n < 0)
	{
		num[len++] = n * -1 + '0';
		num[len++] = '-';
	}
	else
		num[len++] = n + '0';
	num[len] = '\0';
	rev_str(num, len);
	ft_putstr_fd(num, fd);
}
