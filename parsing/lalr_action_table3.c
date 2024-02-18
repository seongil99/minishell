/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_table3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:49:18 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:50:01 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_act_init10(t_table **at)
{
	at[34][10] = (t_table){REDUCE, 14};
	at[35][0] = (t_table){REDUCE, 16};
	at[35][1] = (t_table){REDUCE, 16};
	at[35][2] = (t_table){REDUCE, 16};
	at[35][4] = (t_table){REDUCE, 16};
	at[35][5] = (t_table){REDUCE, 16};
	at[35][6] = (t_table){REDUCE, 16};
	at[35][7] = (t_table){REDUCE, 16};
	at[35][8] = (t_table){REDUCE, 16};
	at[35][9] = (t_table){REDUCE, 16};
	at[35][10] = (t_table){REDUCE, 16};
	at[36][0] = (t_table){REDUCE, 9};
	at[36][1] = (t_table){REDUCE, 9};
	at[36][2] = (t_table){REDUCE, 9};
	at[36][4] = (t_table){REDUCE, 9};
	at[36][6] = (t_table){REDUCE, 9};
	at[36][7] = (t_table){REDUCE, 9};
	at[36][8] = (t_table){REDUCE, 9};
	at[36][9] = (t_table){REDUCE, 9};
	at[36][10] = (t_table){REDUCE, 9};
}
