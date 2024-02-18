/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:54:06 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 14:50:48 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_token	*token_new(char *str, t_gmr_var type)
{
	t_token	*ret;

	ret = ft_calloc2(1, sizeof(t_token));
	ret->str = str;
	if (ret->str)
		ret->str_len = ft_strlen(str);
	ret->type = type;
	return (ret);
}

void	token_del(void *tkn)
{
	t_token	*t;

	t = (t_token *)tkn;
	free(t->str);
	free(t);
}
