/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:45:14 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/15 15:33:37 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char spec, va_list listp)
{
	if (spec == 'c')
		return (ft_print_char(listp));
	else if (spec == 's')
		return (ft_print_string(listp));
	else if (spec == 'p')
		return (ft_print_addr(listp, 16, LOWERHEX));
	else if (spec == 'd' || spec == 'i')
		return (ft_print_num(listp, 10, DECIMAL));
	else if (spec == 'u')
		return (ft_print_unum(listp, 10, DECIMAL));
	else if (spec == 'x')
		return (ft_print_unum(listp, 16, LOWERHEX));
	else if (spec == 'X')
		return (ft_print_unum(listp, 16, UPPERHEX));
	else
		ft_putchar_fd(spec, STDOUT_FILENO);
	return (1);
}

int	do_print(const char *fmt, va_list listp)
{
	int	len;

	len = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			len += print_format(*(++fmt), listp);
		}
		else
		{
			ft_putchar_fd(*fmt, STDOUT_FILENO);
			len++;
		}
		fmt++;
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	listp;
	int		len;

	len = 0;
	va_start(listp, fmt);
	len = do_print(fmt, listp);
	va_end(listp);
	return (len);
}
