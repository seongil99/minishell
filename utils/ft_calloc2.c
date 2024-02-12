/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:09 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 17:51:00 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_utils.h"

void	*ft_calloc2(size_t cnt, size_t size)
{
	void	*ret;

	ret = ft_calloc(cnt, size);
	if (!ret)
		exit_err("MEM Error\n");
	return (ret);
}
