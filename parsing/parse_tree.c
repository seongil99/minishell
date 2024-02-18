/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:23:51 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:18:00 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_treenode	*treenode_new(t_token *data)
{
	t_treenode	*ret;

	ret = ft_calloc2(1, sizeof(t_treenode));
	ret->data = data;
	ret->child = NULL;
	return (ret);
}

void	treenode_del(t_treenode *t)
{
	token_del(t->data);
	lst_clear(&(t->child), do_nothing);
	free(t);
}

void	tree_del(t_treenode	*root)
{
	t_lst		*lt;
	t_treenode	*tt;

	lt = root->child;
	while (lt)
	{
		tt = (t_treenode *)lt->data ;
		tree_del(tt);
		lt = lt->next;
	}
	treenode_del(root);
}

t_treenode	*treenode_add_child_back(t_treenode *node, t_treenode *new_child)
{
	t_lst	*new_lst;

	new_lst = lst_new(new_child);
	lst_push_back(&(node->child), new_lst);
	return (node);
}

t_treenode	*treenode_add_child_front(t_treenode *node, t_treenode *new_child)
{
	t_lst	*new_lst;

	new_lst = lst_new(new_child);
	lst_push_front(&(node->child), new_lst);
	return (node);
}
