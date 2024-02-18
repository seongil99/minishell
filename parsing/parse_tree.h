/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:33:00 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 17:48:30 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H

# include "../utils/mini_utils.h"
# include "../libft/libft.h"
# include "mini_parsing.h"

t_treenode	*treenode_new(t_token *data);
void		treenode_del(t_treenode *t);
void		tree_del(t_treenode	*root);
t_treenode	*treenode_add_child_back(t_treenode *node, t_treenode *new_child);
t_treenode	*treenode_add_child_front(t_treenode *node, t_treenode *new_child);

#endif
