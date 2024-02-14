/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:17:03 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/14 15:15:27 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_TABLE_H
# define LALR_TABLE_H

# include "lalr_parser.h"

# define REJECT 0
# define ACC 1
# define SHIFT 2
# define REDUCE 3
# define GOTO 4

t_table	**get_action_table(void);
t_table	**get_goto_table(void);
void	init_action_table(void);
void	init_goto_table(void);

#endif
