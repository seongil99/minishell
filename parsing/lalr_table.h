/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:17:03 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 18:17:18 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_TABLE_H
# define LALR_TABLE_H

# include "mini_parsing.h"

t_table	**get_action_table(void);
t_table	**get_goto_table(void);
void	init_action_table(void);
void	init_action_tablev2(void);
void	init_goto_table(void);
void	init_goto_tablev2(void);

#endif
