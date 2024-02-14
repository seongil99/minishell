/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/14 14:27:26 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lalr_table.h"

t_table	**get_action_table(void)
{
	static t_table	action_table[11][37];

	return (action_table);
}

t_table	**get_goto_table(void)
{
	static t_table	goto_table[37][14];

	return (goto_table);
}

void	init_action_table(void)
{
	t_table	**at;

	at = get_action_table();
	ft_memset(at, 0, sizeof(t_table) * 11 * 37);
	at[0][3] = (t_table){SHIFT, 7};
	at[0][5] = (t_table){SHIFT, 8};

	at[1][0] = (t_table){SHIFT, 9};
	at[1][1] = (t_table){SHIFT, 10};
	at[1][11] = (t_table){ACC, 0};

	at[2][0] = (t_table){REDUCE, 1};
	at[2][1] = (t_table){REDUCE, 1};
	at[2][2] = (t_table){SHIFT, 11};
	at[2][4] = (t_table){REDUCE, 1};
	at[2][11] = (t_table){REDUCE, 1};

	at[3][0] = (t_table){REDUCE, 4};
	at[3][1] = (t_table){REDUCE, 4};
	at[3][2] = (t_table){REDUCE, 4};
	at[3][4] = (t_table){REDUCE, 4};
	at[3][11] = (t_table){REDUCE, 4};
}

static void	gt_table_init1(t_table **gt)
{
	gt[0][1] = (t_table){GOTO, 1};
	gt[0][2] = (t_table){GOTO, 2};
	gt[0][3] = (t_table){GOTO, 3};
	gt[0][4] = (t_table){GOTO, 5};
	gt[0][5] = (t_table){GOTO, 4};
	gt[0][6] = (t_table){GOTO, 6};
	gt[5][8] = (t_table){GOTO, 12};
	gt[5][9] = (t_table){GOTO, 13};
	gt[5][10] = (t_table){GOTO, 14};
	gt[5][12] = (t_table){GOTO, 15};
	gt[6][7] = (t_table){GOTO, 20};
	gt[6][9] = (t_table){GOTO, 21};
	gt[6][10] = (t_table){GOTO, 14};
	gt[6][12] = (t_table){GOTO, 15};
	gt[7][1] = (t_table){GOTO, 23};
	gt[7][2] = (t_table){GOTO, 2};
	gt[7][3] = (t_table){GOTO, 3};
	gt[7][4] = (t_table){GOTO, 5};
	gt[7][5] = (t_table){GOTO, 4};
	gt[7][6] = (t_table){GOTO, 6};
	gt[9][2] = (t_table){GOTO, 24};
	gt[9][3] = (t_table){GOTO, 3};
	gt[9][4] = (t_table){GOTO, 5};
	gt[9][5] = (t_table){GOTO, 4};
	gt[9][6] = (t_table){GOTO, 6};
}

static void	gt_table_init2(t_table **gt)
{
	gt[10][2] = (t_table){GOTO, 25};
	gt[10][3] = (t_table){GOTO, 3};
	gt[10][4] = (t_table){GOTO, 5};
	gt[10][5] = (t_table){GOTO, 4};
	gt[10][6] = (t_table){GOTO, 6};
	gt[11][3] = (t_table){GOTO, 26};
	gt[11][4] = (t_table){GOTO, 5};
	gt[11][5] = (t_table){GOTO, 4};
	gt[11][6] = (t_table){GOTO, 6};
	gt[12][9] = (t_table){GOTO, 27};
	gt[12][10] = (t_table){GOTO, 14};
	gt[12][12] = (t_table){GOTO, 15};
	gt[16][11] = (t_table){GOTO, 28};
	gt[17][11] = (t_table){GOTO, 30};
	gt[18][11] = (t_table){GOTO, 31};
	gt[19][13] = (t_table){GOTO, 32};
	gt[20][9] = (t_table){GOTO, 34};
	gt[20][10] = (t_table){GOTO, 14};
	gt[20][12] = (t_table){GOTO, 15};
}

void	init_goto_table(void)
{
	t_table	**gt;

	gt = get_goto_table();
	ft_memset(gt, 0, sizeof(t_table) * 37 * 14);
	gt_table_init1(gt);
	gt_table_init2(gt);
}
