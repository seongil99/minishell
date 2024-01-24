/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:03:15 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/26 12:53:07 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_addr(va_list listp, unsigned long long base, char *digits)
{
	unsigned long long	addr;
	unsigned long long	len;
	unsigned long long	i;
	char				buf[50];

	len = 0;
	addr = (unsigned long long)va_arg(listp, void *);
	while (addr / base)
	{
		i = addr % base;
		buf[len++] = digits[i];
		addr /= base;
	}
	buf[len++] = digits[addr];
	buf[len] = '\0';
	ft_print_rev(buf, len);
	ft_putstr_fd("0x", STDOUT_FILENO);
	ft_putstr_fd(buf, STDOUT_FILENO);
	return (len + 2);
}
