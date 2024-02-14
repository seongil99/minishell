/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:33:00 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 20:36:41 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H

# include "scanner.h"
# include "../utils/mini_utils.h"
# include "../libft/libft.h"

typedef struct s_treenode
{
	t_token				*data;
	struct s_treenode	*child;
}	t_treenode;

#endif
