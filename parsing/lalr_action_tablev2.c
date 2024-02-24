/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_tablev2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:02:44 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 20:14:21 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_init_action_table5(t_table **at);
void	_init_action_table6(t_table **at);
void	_init_action_table7(t_table **at);
void	_init_action_table8(t_table **at);
void	_init_action_table9(t_table **at);
void	_init_action_table10(t_table **at);
void	_init_action_table11(t_table **at);
void	_init_action_table12(t_table **at);
void	_init_action_table13(t_table **at);

static void	_init_action_table1(t_table **at)
{
	at[0][3] = (t_table){SHIFT, 8};
	at[0][5] = (t_table){SHIFT, 10};
	at[0][6] = (t_table){SHIFT, 13};
	at[0][7] = (t_table){SHIFT, 14};
	at[0][8] = (t_table){SHIFT, 15};
	at[0][9] = (t_table){SHIFT, 16};
	at[1][0] = (t_table){SHIFT, 17};
	at[1][1] = (t_table){SHIFT, 18};
	at[1][10] = (t_table){ACC, 0};
	at[2][0] = (t_table){REDUCE, 1};
	at[2][1] = (t_table){REDUCE, 1};
	at[2][2] = (t_table){SHIFT, 19};
	at[2][4] = (t_table){REDUCE, 1};
	at[2][10] = (t_table){REDUCE, 1};
	at[3][0] = (t_table){REDUCE, 4};
	at[3][1] = (t_table){REDUCE, 4};
	at[3][2] = (t_table){REDUCE, 4};
	at[3][4] = (t_table){REDUCE, 4};
	at[3][10] = (t_table){REDUCE, 4};
	at[4][0] = (t_table){REDUCE, 6};
	at[4][1] = (t_table){REDUCE, 6};
	at[4][2] = (t_table){REDUCE, 6};
	at[4][4] = (t_table){REDUCE, 6};
	at[4][10] = (t_table){REDUCE, 6};
	at[5][0] = (t_table){REDUCE, 7};
}

static void	_init_action_table2(t_table **at)
{
	at[5][1] = (t_table){REDUCE, 7};
	at[5][2] = (t_table){REDUCE, 7};
	at[5][4] = (t_table){REDUCE, 7};
	at[5][6] = (t_table){SHIFT, 13};
	at[5][7] = (t_table){SHIFT, 14};
	at[5][8] = (t_table){SHIFT, 15};
	at[5][9] = (t_table){SHIFT, 16};
	at[5][10] = (t_table){REDUCE, 7};
	at[6][0] = (t_table){REDUCE, 12};
	at[6][1] = (t_table){REDUCE, 12};
	at[6][2] = (t_table){REDUCE, 12};
	at[6][4] = (t_table){REDUCE, 12};
	at[6][5] = (t_table){SHIFT, 10};
	at[6][6] = (t_table){SHIFT, 13};
	at[6][7] = (t_table){SHIFT, 14};
	at[6][8] = (t_table){SHIFT, 15};
	at[6][9] = (t_table){SHIFT, 16};
	at[6][10] = (t_table){REDUCE, 12};
	at[7][0] = (t_table){REDUCE, 14};
	at[7][1] = (t_table){REDUCE, 14};
	at[7][2] = (t_table){REDUCE, 14};
	at[7][4] = (t_table){REDUCE, 14};
	at[7][5] = (t_table){SHIFT, 26};
	at[7][6] = (t_table){SHIFT, 13};
	at[7][7] = (t_table){SHIFT, 14};
}

static void	_init_action_table3(t_table **at)
{
	at[7][8] = (t_table){SHIFT, 15};
	at[7][9] = (t_table){SHIFT, 16};
	at[7][10] = (t_table){REDUCE, 14};
	at[8][3] = (t_table){SHIFT, 8};
	at[8][5] = (t_table){SHIFT, 10};
	at[8][6] = (t_table){SHIFT, 13};
	at[8][7] = (t_table){SHIFT, 14};
	at[8][8] = (t_table){SHIFT, 15};
	at[8][9] = (t_table){SHIFT, 16};
	at[9][0] = (t_table){REDUCE, 16};
	at[9][1] = (t_table){REDUCE, 16};
	at[9][2] = (t_table){REDUCE, 16};
	at[9][4] = (t_table){REDUCE, 16};
	at[9][5] = (t_table){REDUCE, 16};
	at[9][6] = (t_table){REDUCE, 16};
	at[9][7] = (t_table){REDUCE, 16};
	at[9][8] = (t_table){REDUCE, 16};
	at[9][9] = (t_table){REDUCE, 16};
	at[9][10] = (t_table){REDUCE, 16};
	at[10][0] = (t_table){REDUCE, 15};
	at[10][1] = (t_table){REDUCE, 15};
	at[10][2] = (t_table){REDUCE, 15};
	at[10][4] = (t_table){REDUCE, 15};
	at[10][5] = (t_table){REDUCE, 15};
	at[10][6] = (t_table){REDUCE, 15};
}

static void	_init_action_table4(t_table **at)
{
	at[10][6] = (t_table){REDUCE, 15};
	at[10][7] = (t_table){REDUCE, 15};
	at[10][8] = (t_table){REDUCE, 15};
	at[10][9] = (t_table){REDUCE, 15};
	at[10][10] = (t_table){REDUCE, 15};
	at[11][0] = (t_table){REDUCE, 24};
	at[11][1] = (t_table){REDUCE, 24};
	at[11][2] = (t_table){REDUCE, 24};
	at[11][4] = (t_table){REDUCE, 24};
	at[11][5] = (t_table){REDUCE, 24};
	at[11][6] = (t_table){REDUCE, 24};
	at[11][7] = (t_table){REDUCE, 24};
	at[11][8] = (t_table){REDUCE, 24};
	at[11][9] = (t_table){REDUCE, 24};
	at[11][10] = (t_table){REDUCE, 24};
	at[12][0] = (t_table){REDUCE, 25};
	at[12][1] = (t_table){REDUCE, 25};
	at[12][2] = (t_table){REDUCE, 25};
	at[12][4] = (t_table){REDUCE, 25};
	at[12][5] = (t_table){REDUCE, 25};
	at[12][6] = (t_table){REDUCE, 25};
	at[12][7] = (t_table){REDUCE, 25};
	at[12][8] = (t_table){REDUCE, 25};
	at[12][9] = (t_table){REDUCE, 25};
}

void	init_action_tablev2(void)
{
	t_table	**at;

	at = get_action_table();
	_init_action_table1(at);
	_init_action_table2(at);
	_init_action_table3(at);
	_init_action_table4(at);
	_init_action_table5(at);
	_init_action_table6(at);
	_init_action_table7(at);
	_init_action_table8(at);
	_init_action_table9(at);
	_init_action_table10(at);
	_init_action_table11(at);
	_init_action_table12(at);
	_init_action_table13(at);
}
