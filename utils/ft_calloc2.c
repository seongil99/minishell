/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:09 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/16 10:26:43 by sihkang          ###   ########seoul.kr  */
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
