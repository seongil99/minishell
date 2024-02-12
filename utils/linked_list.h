/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:45:23 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 16:21:07 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct s_lst
{
	void			*data;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

t_lst	*lst_new(void *data);
void	lst_del(t_lst **lst, t_lst *target);
void	lst_clear(t_lst **head);
void	lst_push_front(t_lst **head, t_lst *newlst);
void	lst_push_back(t_lst **head, t_lst *newlst);
t_lst	*ft_lstlast(t_lst *lst);

#endif
