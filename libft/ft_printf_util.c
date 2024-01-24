/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:23:20 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/26 12:51:29 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_print_rev(char *s, size_t len)
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

int	ft_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}
