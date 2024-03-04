/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:38:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/21 17:45:00 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_PARSER_H
# define LALR_PARSER_H

# include "../utils/mini_utils.h"
# include "../libft/libft.h"
# include "parsing_type.h"

int			lalr_shift(t_automata *at, t_table t);
int			lalr_reduce(t_automata *at, t_table t);
int			lalr_goto(t_automata *at, t_table t);
int			parse_line(t_lst *lst);
void		table_clear(void);
int			lalr_action(t_automata *at, t_table t);
int			auto_transition(t_automata *at);
t_automata	*automata_new(t_lst *input);
void		automata_del(t_automata *at);
int			auto_get_state(t_automata *at);
int			quote_check(char *str);

#endif
