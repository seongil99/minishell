/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/16 17:11:27 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalr_table.h"

void	table_clear(void)
{
	t_table	**t1;
	t_table	**t2;
	int		i;

	t1 = get_action_table();
	t2 = get_goto_table();
	i = 0;
	while (i < 37)
	{
		free(t1[i]);
		free(t2[i]);
		i++;
	}
	free(t1);
	free(t2);
}

t_table	**get_action_table(void)
{
	static t_table	**action_table;
	int				i;

	if (!action_table)
	{
		action_table = ft_calloc2(37, sizeof(t_table *));
		i = 0;
		while (i < 37)
		{
			action_table[i] = ft_calloc2(11, sizeof(t_table));
			i++;
		}
	}
	return (action_table);
}

t_table	**get_goto_table(void)
{
	static t_table	**goto_table;
	int				i;

	if (!goto_table)
	{
		goto_table = ft_calloc2(37, sizeof(t_table *));
		i = 0;
		while (i < 37)
		{
			goto_table[i] = ft_calloc2(14, sizeof(t_table));
			i++;
		}
	}
	return (goto_table);
}

void	init_action_table(void)
{
	t_table	**at;

	at = get_action_table();
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
	at[20][1] = (t_table){REDUCE, 10};
	at[20][2] = (t_table){REDUCE, 10};
	at[20][4] = (t_table){REDUCE, 10};
	at[20][5] = (t_table){SHIFT, 35};
	at[20][6] = (t_table){SHIFT, 16};
	at[20][7] = (t_table){SHIFT, 17};
	at[20][8] = (t_table){SHIFT, 18};
	at[20][9] = (t_table){SHIFT, 19};
	at[20][10] = (t_table){REDUCE, 10};

	at[21][0] = (t_table){REDUCE, 13};
	at[21][1] = (t_table){REDUCE, 13};
	at[21][2] = (t_table){REDUCE, 13};
	at[21][4] = (t_table){REDUCE, 13};
	at[21][5] = (t_table){REDUCE, 13};
	at[21][6] = (t_table){REDUCE, 13};
	at[21][7] = (t_table){REDUCE, 13};
	at[21][8] = (t_table){REDUCE, 13};
	at[21][9] = (t_table){REDUCE, 13};
	at[21][10] = (t_table){REDUCE, 13};

	at[22][0] = (t_table){REDUCE, 15};
	at[22][1] = (t_table){REDUCE, 15};
	at[22][2] = (t_table){REDUCE, 15};
	at[22][4] = (t_table){REDUCE, 15};
	at[22][5] = (t_table){REDUCE, 15};
	at[22][6] = (t_table){REDUCE, 15};
	at[22][7] = (t_table){REDUCE, 15};
	at[22][8] = (t_table){REDUCE, 15};
	at[22][9] = (t_table){REDUCE, 15};
	at[22][10] = (t_table){REDUCE, 15};

	at[23][0] = (t_table){SHIFT, 9};
	at[23][1] = (t_table){SHIFT, 10};
	at[23][4] = (t_table){SHIFT, 36};

	at[24][0] = (t_table){REDUCE, 2};
	at[24][1] = (t_table){REDUCE, 2};
	at[24][2] = (t_table){SHIFT, 11};
	at[24][4] = (t_table){REDUCE, 2};
	at[24][10] = (t_table){REDUCE, 2};

	at[25][0] = (t_table){REDUCE, 3};
	at[25][1] = (t_table){REDUCE, 3};
	at[25][2] = (t_table){SHIFT, 11};
	at[25][4] = (t_table){REDUCE, 3};
	at[25][10] = (t_table){REDUCE, 3};

	at[26][0] = (t_table){REDUCE, 5};
	at[26][1] = (t_table){REDUCE, 5};
	at[26][2] = (t_table){REDUCE, 5};
	at[26][4] = (t_table){REDUCE, 5};
	at[26][10] = (t_table){REDUCE, 5};

	at[27][0] = (t_table){REDUCE, 18};
	at[27][1] = (t_table){REDUCE, 18};
	at[27][2] = (t_table){REDUCE, 18};
	at[27][4] = (t_table){REDUCE, 18};
	at[27][6] = (t_table){REDUCE, 18};
	at[27][7] = (t_table){REDUCE, 18};
	at[27][8] = (t_table){REDUCE, 18};
	at[27][9] = (t_table){REDUCE, 18};
	at[27][10] = (t_table){REDUCE, 18};

	at[28][0] = (t_table){REDUCE, 21};
	at[28][1] = (t_table){REDUCE, 21};
	at[28][2] = (t_table){REDUCE, 21};
	at[28][4] = (t_table){REDUCE, 21};
	at[28][5] = (t_table){REDUCE, 21};
	at[28][6] = (t_table){REDUCE, 21};
	at[28][7] = (t_table){REDUCE, 21};
	at[28][8] = (t_table){REDUCE, 21};
	at[28][9] = (t_table){REDUCE, 21};
	at[28][10] = (t_table){REDUCE, 21};

	at[29][0] = (t_table){REDUCE, 24};
	at[29][1] = (t_table){REDUCE, 24};
	at[29][2] = (t_table){REDUCE, 24};
	at[29][4] = (t_table){REDUCE, 24};
	at[29][5] = (t_table){REDUCE, 24};
	at[29][6] = (t_table){REDUCE, 24};
	at[29][7] = (t_table){REDUCE, 24};
	at[29][8] = (t_table){REDUCE, 24};
	at[29][9] = (t_table){REDUCE, 24};
	at[29][10] = (t_table){REDUCE, 24};

	at[30][0] = (t_table){REDUCE, 22};
	at[30][1] = (t_table){REDUCE, 22};
	at[30][2] = (t_table){REDUCE, 22};
	at[30][4] = (t_table){REDUCE, 22};
	at[30][5] = (t_table){REDUCE, 22};
	at[30][6] = (t_table){REDUCE, 22};
	at[30][7] = (t_table){REDUCE, 22};
	at[30][8] = (t_table){REDUCE, 22};
	at[30][9] = (t_table){REDUCE, 22};
	at[30][10] = (t_table){REDUCE, 22};

	at[31][0] = (t_table){REDUCE, 23};
	at[31][1] = (t_table){REDUCE, 23};
	at[31][2] = (t_table){REDUCE, 23};
	at[31][4] = (t_table){REDUCE, 23};
	at[31][5] = (t_table){REDUCE, 23};
	at[31][6] = (t_table){REDUCE, 23};
	at[31][7] = (t_table){REDUCE, 23};
	at[31][8] = (t_table){REDUCE, 23};
	at[31][9] = (t_table){REDUCE, 23};
	at[31][10] = (t_table){REDUCE, 23};

	at[32][0] = (t_table){REDUCE, 25};
	at[32][1] = (t_table){REDUCE, 25};
	at[32][2] = (t_table){REDUCE, 25};
	at[32][4] = (t_table){REDUCE, 25};
	at[32][5] = (t_table){REDUCE, 25};
	at[32][6] = (t_table){REDUCE, 25};
	at[32][7] = (t_table){REDUCE, 25};
	at[32][8] = (t_table){REDUCE, 25};
	at[32][9] = (t_table){REDUCE, 25};
	at[32][10] = (t_table){REDUCE, 25};

	at[33][0] = (t_table){REDUCE, 26};
	at[33][1] = (t_table){REDUCE, 26};
	at[33][2] = (t_table){REDUCE, 26};
	at[33][4] = (t_table){REDUCE, 26};
	at[33][5] = (t_table){REDUCE, 26};
	at[33][6] = (t_table){REDUCE, 26};
	at[33][7] = (t_table){REDUCE, 26};
	at[33][8] = (t_table){REDUCE, 26};
	at[33][9] = (t_table){REDUCE, 26};
	at[33][10] = (t_table){REDUCE, 26};

	at[34][0] = (t_table){REDUCE, 14};
	at[34][1] = (t_table){REDUCE, 14};
	at[34][2] = (t_table){REDUCE, 14};
	at[34][4] = (t_table){REDUCE, 14};
	at[34][5] = (t_table){REDUCE, 14};
	at[34][6] = (t_table){REDUCE, 14};
	at[34][7] = (t_table){REDUCE, 14};
	at[34][8] = (t_table){REDUCE, 14};
	at[34][9] = (t_table){REDUCE, 14};
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
	gt_table_init1(gt);
	gt_table_init2(gt);
}
