/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:38:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 17:48:55 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_PARSER_H
# define LALR_PARSER_H

# include "../utils/mini_utils.h"
# include "../libft/libft.h"
# include "parse_tree.h"

/////
# include <stdio.h>
/////


int			lalr_shift(t_automata *at, t_stack *tree_stack, t_table t);
int			lalr_reduce(t_automata *at, t_stack *tree_stack, t_table t);
int			lalr_goto(t_automata *at, t_table t);
t_treenode	*parse_line(t_lst *lst);
void		table_clear(void);

#endif
