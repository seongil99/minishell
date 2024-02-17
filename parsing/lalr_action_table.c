/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:19:13 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:50:46 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_act_init5(t_table **at);
void	_act_init6(t_table **at);
void	_act_init7(t_table **at);
void	_act_init8(t_table **at);
void	_act_init9(t_table **at);
void	_act_init10(t_table **at);

static void	_act_init1(t_table **at)
{
	at[0][3] = (t_table){SHIFT, 7};
	at[0][5] = (t_table){SHIFT, 8};
	at[1][0] = (t_table){SHIFT, 9};
	at[1][1] = (t_table){SHIFT, 10};
	at[1][10] = (t_table){ACC, 0};
	at[2][0] = (t_table){REDUCE, 1};
	at[2][1] = (t_table){REDUCE, 1};
	at[2][2] = (t_table){SHIFT, 11};
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
	at[5][1] = (t_table){REDUCE, 7};
	at[5][2] = (t_table){REDUCE, 7};
	at[5][4] = (t_table){REDUCE, 7};
	at[5][6] = (t_table){SHIFT, 16};
}

static void	_act_init2(t_table **at)
{
	at[5][7] = (t_table){SHIFT, 17};
	at[5][8] = (t_table){SHIFT, 18};
	at[5][9] = (t_table){SHIFT, 19};
	at[5][10] = (t_table){REDUCE, 7};
	at[6][0] = (t_table){REDUCE, 11};
	at[6][1] = (t_table){REDUCE, 11};
	at[6][2] = (t_table){REDUCE, 11};
	at[6][4] = (t_table){REDUCE, 11};
	at[6][5] = (t_table){SHIFT, 22};
	at[6][6] = (t_table){SHIFT, 16};
	at[6][7] = (t_table){SHIFT, 17};
	at[6][8] = (t_table){SHIFT, 18};
	at[6][9] = (t_table){SHIFT, 19};
	at[6][10] = (t_table){REDUCE, 11};
	at[7][3] = (t_table){SHIFT, 7};
	at[7][5] = (t_table){SHIFT, 8};
	at[8][0] = (t_table){REDUCE, 12};
	at[8][1] = (t_table){REDUCE, 12};
	at[8][2] = (t_table){REDUCE, 12};
	at[8][4] = (t_table){REDUCE, 12};
	at[8][5] = (t_table){REDUCE, 12};
	at[8][6] = (t_table){REDUCE, 12};
	at[8][7] = (t_table){REDUCE, 12};
	at[8][8] = (t_table){REDUCE, 12};
	at[8][9] = (t_table){REDUCE, 12};
}

static void	_act_init3(t_table **at)
{
	at[8][10] = (t_table){REDUCE, 12};
	at[9][3] = (t_table){SHIFT, 7};
	at[9][5] = (t_table){SHIFT, 8};
	at[10][3] = (t_table){SHIFT, 7};
	at[10][5] = (t_table){SHIFT, 8};
	at[11][3] = (t_table){SHIFT, 7};
	at[11][5] = (t_table){SHIFT, 8};
	at[12][0] = (t_table){REDUCE, 8};
	at[12][1] = (t_table){REDUCE, 8};
	at[12][2] = (t_table){REDUCE, 8};
	at[12][4] = (t_table){REDUCE, 8};
	at[12][6] = (t_table){SHIFT, 16};
	at[12][7] = (t_table){SHIFT, 17};
	at[12][8] = (t_table){SHIFT, 18};
	at[12][9] = (t_table){SHIFT, 19};
	at[12][10] = (t_table){REDUCE, 8};
	at[13][0] = (t_table){REDUCE, 17};
	at[13][1] = (t_table){REDUCE, 17};
	at[13][2] = (t_table){REDUCE, 17};
	at[13][4] = (t_table){REDUCE, 17};
	at[13][6] = (t_table){REDUCE, 17};
	at[13][7] = (t_table){REDUCE, 17};
	at[13][8] = (t_table){REDUCE, 17};
	at[13][9] = (t_table){REDUCE, 17};
	at[13][10] = (t_table){REDUCE, 17};
}

static void	_act_init4(t_table **at)
{
	at[14][0] = (t_table){REDUCE, 19};
	at[14][1] = (t_table){REDUCE, 19};
	at[14][2] = (t_table){REDUCE, 19};
	at[14][4] = (t_table){REDUCE, 19};
	at[14][5] = (t_table){REDUCE, 19};
	at[14][6] = (t_table){REDUCE, 19};
	at[14][7] = (t_table){REDUCE, 19};
	at[14][8] = (t_table){REDUCE, 19};
	at[14][9] = (t_table){REDUCE, 19};
	at[14][10] = (t_table){REDUCE, 19};
	at[15][0] = (t_table){REDUCE, 20};
	at[15][1] = (t_table){REDUCE, 20};
	at[15][2] = (t_table){REDUCE, 20};
	at[15][4] = (t_table){REDUCE, 20};
	at[15][5] = (t_table){REDUCE, 20};
	at[15][6] = (t_table){REDUCE, 20};
	at[15][7] = (t_table){REDUCE, 20};
	at[15][8] = (t_table){REDUCE, 20};
	at[15][9] = (t_table){REDUCE, 20};
	at[15][10] = (t_table){REDUCE, 20};
	at[16][5] = (t_table){SHIFT, 29};
	at[17][5] = (t_table){SHIFT, 29};
	at[18][5] = (t_table){SHIFT, 29};
	at[19][5] = (t_table){SHIFT, 33};
	at[20][0] = (t_table){REDUCE, 10};
}

void	init_action_table(void)
{
	t_table	**at;

	at = get_action_table();
	_act_init1(at);
	_act_init2(at);
	_act_init3(at);
	_act_init4(at);
	_act_init5(at);
	_act_init6(at);
	_act_init7(at);
	_act_init8(at);
	_act_init9(at);
	_act_init10(at);
}
