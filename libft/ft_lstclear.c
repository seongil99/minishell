/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:03:23 by seonyoon          #+#    #+#             */
/*   Updated: 2023/10/20 12:53:38 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (!lst || !(*lst))
		return ;
	while (*lst)
	{
		nxt = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = nxt;
	}
}
