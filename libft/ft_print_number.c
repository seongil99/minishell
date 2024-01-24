/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:48:43 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/26 12:53:13 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_num(va_list listp, int base, char *digits)
{
	int		n;
	int		len;
	int		i;
	char	buf[50];

	len = 0;
	n = va_arg(listp, int);
	while (n / base)
	{
		i = ft_abs(n % base);
		buf[len++] = digits[i];
		n /= base;
	}
	buf[len++] = digits[ft_abs(n)];
	if (n < 0)
		buf[len++] = '-';
	buf[len] = '\0';
	ft_print_rev(buf, len);
	ft_putstr_fd(buf, STDOUT_FILENO);
	return (len);
}

int	ft_print_unum(va_list listp, unsigned int base, char *digits)
{
	unsigned int	n;
	unsigned int	len;
	unsigned int	i;
	char			buf[50];

	len = 0;
	n = va_arg(listp, unsigned int);
	while (n / base)
	{
		i = n % base;
		buf[len++] = digits[i];
		n /= base;
	}
	buf[len++] = digits[n];
	buf[len] = '\0';
	ft_print_rev(buf, len);
	ft_putstr_fd(buf, STDOUT_FILENO);
	return (len);
}
