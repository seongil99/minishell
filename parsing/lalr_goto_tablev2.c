/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_goto_tablev2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:39:58 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 20:00:10 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

static void	_init_goto_table1(t_table **gt)
{
	gt[0][1] = (t_table){GOTO, 1};
	gt[0][2] = (t_table){GOTO, 2};
	gt[0][3] = (t_table){GOTO, 3};
	gt[0][4] = (t_table){GOTO, 5};
	gt[0][5] = (t_table){GOTO, 4};
	gt[0][6] = (t_table){GOTO, 7};
	gt[0][7] = (t_table){GOTO, 6};
	gt[0][10] = (t_table){GOTO, 9};
	gt[0][11] = (t_table){GOTO, 11};
	gt[0][13] = (t_table){GOTO, 12};
	gt[5][9] = (t_table){GOTO, 20};
	gt[5][10] = (t_table){GOTO, 21};
	gt[5][11] = (t_table){GOTO, 11};
	gt[5][13] = (t_table){GOTO, 12};
	gt[6][6] = (t_table){GOTO, 22};
	gt[6][10] = (t_table){GOTO, 23};
	gt[6][11] = (t_table){GOTO, 11};
	gt[6][13] = (t_table){GOTO, 12};
	gt[7][8] = (t_table){GOTO, 24};
	gt[7][10] = (t_table){GOTO, 25};
	gt[7][11] = (t_table){GOTO, 11};
	gt[7][13] = (t_table){GOTO, 12};
	gt[8][1] = (t_table){GOTO, 27};
	gt[8][2] = (t_table){GOTO, 2};
	gt[8][3] = (t_table){GOTO, 3};
}

static void	_init_goto_table2(t_table **gt)
{
	gt[8][4] = (t_table){GOTO, 5};
	gt[8][5] = (t_table){GOTO, 4};
	gt[8][6] = (t_table){GOTO, 7};
	gt[8][7] = (t_table){GOTO, 6};
	gt[8][10] = (t_table){GOTO, 9};
	gt[8][11] = (t_table){GOTO, 11};
	gt[8][13] = (t_table){GOTO, 12};
	gt[13][12] = (t_table){GOTO, 28};
	gt[14][12] = (t_table){GOTO, 30};
	gt[15][12] = (t_table){GOTO, 31};
	gt[16][14] = (t_table){GOTO, 32};
	gt[17][2] = (t_table){GOTO, 34};
	gt[17][3] = (t_table){GOTO, 3};
	gt[17][4] = (t_table){GOTO, 5};
	gt[17][5] = (t_table){GOTO, 4};
	gt[17][6] = (t_table){GOTO, 7};
	gt[17][7] = (t_table){GOTO, 6};
	gt[17][10] = (t_table){GOTO, 9};
	gt[17][11] = (t_table){GOTO, 11};
	gt[17][13] = (t_table){GOTO, 12};
	gt[18][2] = (t_table){GOTO, 35};
	gt[18][3] = (t_table){GOTO, 3};
	gt[18][4] = (t_table){GOTO, 5};
	gt[18][5] = (t_table){GOTO, 4};
	gt[18][6] = (t_table){GOTO, 7};
}

static void	_init_goto_table3(t_table **gt)
{
	gt[18][6] = (t_table){GOTO, 7};
	gt[18][7] = (t_table){GOTO, 6};
	gt[18][10] = (t_table){GOTO, 9};
	gt[18][11] = (t_table){GOTO, 11};
	gt[18][13] = (t_table){GOTO, 12};
	gt[19][3] = (t_table){GOTO, 36};
	gt[19][4] = (t_table){GOTO, 5};
	gt[19][5] = (t_table){GOTO, 4};
	gt[19][6] = (t_table){GOTO, 7};
	gt[19][7] = (t_table){GOTO, 6};
	gt[19][10] = (t_table){GOTO, 9};
	gt[19][11] = (t_table){GOTO, 11};
	gt[19][13] = (t_table){GOTO, 12};
	gt[20][10] = (t_table){GOTO, 37};
	gt[20][11] = (t_table){GOTO, 11};
	gt[20][13] = (t_table){GOTO, 12};
	gt[22][8] = (t_table){GOTO, 38};
	gt[22][10] = (t_table){GOTO, 25};
	gt[22][11] = (t_table){GOTO, 11};
	gt[22][13] = (t_table){GOTO, 12};
	gt[24][10] = (t_table){GOTO, 39};
	gt[24][11] = (t_table){GOTO, 11};
	gt[24][13] = (t_table){GOTO, 12};
	gt[38][10] = (t_table){GOTO, 39};
}

void	init_goto_tablev2(void)
{
	t_table	**gt;

	gt = get_goto_table();
	_init_goto_table1(gt);
	_init_goto_table2(gt);
	_init_goto_table3(gt);
	gt[38][11] = (t_table){GOTO, 11};
	gt[38][13] = (t_table){GOTO, 12};
}
