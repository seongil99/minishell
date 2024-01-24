/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:30:04 by seonyoon          #+#    #+#             */
/*   Updated: 2023/11/10 17:01:27 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	append_lstmap(t_list *lst, t_list **ret,
		void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	void	*new_content;

	new_content = (*f)(lst->content);
	if (!new_content)
	{
		return (0);
	}
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		(*del)(new_content);
		return (0);
	}
	ft_lstadd_back(ret, new_node);
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;

	if (!lst)
		return (0);
	ret = 0;
	while (lst)
	{
		if (!append_lstmap(lst, &ret, f, del))
		{
			ft_lstclear(&ret, del);
		}
		lst = lst->next;
	}
	return (ret);
}
