/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:46:19 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/26 12:51:20 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define UPPERHEX "0123456789ABCDEF"
# define LOWERHEX "0123456789abcdef"
# define DECIMAL "0123456789"

int		ft_printf(const char *fmt, ...);
int		ft_print_char(va_list listp);
int		ft_print_string(va_list listp);
int		ft_print_num(va_list listp, int base, char *digits);
int		ft_print_unum(va_list listp, unsigned int base, char *digits);
int		ft_print_addr(va_list listp, unsigned long long base, char *digits);
char	*ft_print_rev(char *s, size_t len);
int		ft_abs(int n);

#endif
