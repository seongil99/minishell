/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:41:11 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/05 12:36:19 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"
#include "../expansions/expansions.h"

int	quote_check(char *str)
{
	int	flag;

	flag = NO_QUOTE;
	while (*str)
	{
		set_quote_flag(&flag, *str, str);
		str++;
	}
	if (flag == NO_QUOTE)
		return (ACC);
	return (REJECT);
}
