/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_tablev21.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:05:25 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 20:08:42 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_init_action_table5(t_table **at)
{
	at[12][10] = (t_table){REDUCE, 25};
	at[13][5] = (t_table){SHIFT, 29};
	at[14][5] = (t_table){SHIFT, 29};
	at[15][5] = (t_table){SHIFT, 29};
	at[16][5] = (t_table){SHIFT, 33};
	at[17][3] = (t_table){SHIFT, 8};
	at[17][5] = (t_table){SHIFT, 10};
	at[17][6] = (t_table){SHIFT, 13};
	at[17][7] = (t_table){SHIFT, 14};
	at[17][8] = (t_table){SHIFT, 15};
	at[17][9] = (t_table){SHIFT, 16};
	at[18][3] = (t_table){SHIFT, 8};
	at[18][5] = (t_table){SHIFT, 10};
	at[18][6] = (t_table){SHIFT, 13};
	at[18][7] = (t_table){SHIFT, 14};
	at[18][8] = (t_table){SHIFT, 15};
	at[18][9] = (t_table){SHIFT, 16};
	at[19][3] = (t_table){SHIFT, 8};
	at[19][5] = (t_table){SHIFT, 10};
	at[19][6] = (t_table){SHIFT, 13};
	at[19][7] = (t_table){SHIFT, 14};
	at[19][8] = (t_table){SHIFT, 15};
	at[19][9] = (t_table){SHIFT, 16};
	at[20][0] = (t_table){REDUCE, 8};
}

void	_init_action_table6(t_table **at)
{
	at[20][1] = (t_table){REDUCE, 8};
	at[20][2] = (t_table){REDUCE, 8};
	at[20][4] = (t_table){REDUCE, 8};
	at[20][6] = (t_table){SHIFT, 13};
	at[20][7] = (t_table){SHIFT, 14};
	at[20][8] = (t_table){SHIFT, 15};
	at[20][9] = (t_table){SHIFT, 16};
	at[20][10] = (t_table){REDUCE, 8};
	at[21][0] = (t_table){REDUCE, 22};
	at[21][1] = (t_table){REDUCE, 22};
	at[21][2] = (t_table){REDUCE, 22};
	at[21][4] = (t_table){REDUCE, 22};
	at[21][6] = (t_table){REDUCE, 22};
	at[21][7] = (t_table){REDUCE, 22};
	at[21][8] = (t_table){REDUCE, 22};
	at[21][9] = (t_table){REDUCE, 22};
	at[21][10] = (t_table){REDUCE, 22};
	at[22][0] = (t_table){REDUCE, 11};
	at[22][1] = (t_table){REDUCE, 11};
	at[22][2] = (t_table){REDUCE, 11};
	at[22][4] = (t_table){REDUCE, 11};
	at[22][5] = (t_table){SHIFT, 26};
	at[22][6] = (t_table){SHIFT, 13};
	at[22][7] = (t_table){SHIFT, 14};
	at[22][8] = (t_table){SHIFT, 15};
}

void	_init_action_table7(t_table **at)
{
	at[22][9] = (t_table){SHIFT, 16};
	at[22][10] = (t_table){REDUCE, 11};
	at[23][0] = (t_table){REDUCE, 17};
	at[23][1] = (t_table){REDUCE, 17};
	at[23][2] = (t_table){REDUCE, 17};
	at[23][4] = (t_table){REDUCE, 17};
	at[23][5] = (t_table){REDUCE, 17};
	at[23][6] = (t_table){REDUCE, 17};
	at[23][7] = (t_table){REDUCE, 17};
	at[23][8] = (t_table){REDUCE, 17};
	at[23][9] = (t_table){REDUCE, 17};
	at[23][10] = (t_table){REDUCE, 17};
	at[24][0] = (t_table){REDUCE, 13};
	at[24][1] = (t_table){REDUCE, 13};
	at[24][2] = (t_table){REDUCE, 13};
	at[24][4] = (t_table){REDUCE, 13};
	at[24][5] = (t_table){SHIFT, 40};
	at[24][6] = (t_table){SHIFT, 13};
	at[24][7] = (t_table){SHIFT, 14};
	at[24][8] = (t_table){SHIFT, 15};
	at[24][9] = (t_table){SHIFT, 16};
	at[24][10] = (t_table){REDUCE, 13};
	at[25][0] = (t_table){REDUCE, 18};
	at[25][1] = (t_table){REDUCE, 18};
	at[25][2] = (t_table){REDUCE, 18};
}

void	_init_action_table8(t_table **at)
{
	at[25][2] = (t_table){REDUCE, 18};
	at[25][4] = (t_table){REDUCE, 18};
	at[25][5] = (t_table){REDUCE, 18};
	at[25][6] = (t_table){REDUCE, 18};
	at[25][7] = (t_table){REDUCE, 18};
	at[25][8] = (t_table){REDUCE, 18};
	at[25][9] = (t_table){REDUCE, 18};
	at[25][10] = (t_table){REDUCE, 18};
	at[26][0] = (t_table){REDUCE, 20};
	at[26][1] = (t_table){REDUCE, 20};
	at[26][2] = (t_table){REDUCE, 20};
	at[26][4] = (t_table){REDUCE, 20};
	at[26][5] = (t_table){REDUCE, 20};
	at[26][6] = (t_table){REDUCE, 20};
	at[26][7] = (t_table){REDUCE, 20};
	at[26][8] = (t_table){REDUCE, 20};
	at[26][9] = (t_table){REDUCE, 20};
	at[26][10] = (t_table){REDUCE, 20};
	at[27][0] = (t_table){SHIFT, 17};
	at[27][1] = (t_table){SHIFT, 18};
	at[27][4] = (t_table){SHIFT, 41};
	at[28][0] = (t_table){REDUCE, 26};
	at[28][1] = (t_table){REDUCE, 26};
	at[28][2] = (t_table){REDUCE, 26};
	at[28][4] = (t_table){REDUCE, 26};
}

void	_init_action_table9(t_table **at)
{
	at[28][5] = (t_table){REDUCE, 26};
	at[28][6] = (t_table){REDUCE, 26};
	at[28][7] = (t_table){REDUCE, 26};
	at[28][8] = (t_table){REDUCE, 26};
	at[28][9] = (t_table){REDUCE, 26};
	at[28][10] = (t_table){REDUCE, 26};
	at[29][0] = (t_table){REDUCE, 29};
	at[29][1] = (t_table){REDUCE, 29};
	at[29][2] = (t_table){REDUCE, 29};
	at[29][4] = (t_table){REDUCE, 29};
	at[29][5] = (t_table){REDUCE, 29};
	at[29][6] = (t_table){REDUCE, 29};
	at[29][7] = (t_table){REDUCE, 29};
	at[29][8] = (t_table){REDUCE, 29};
	at[29][9] = (t_table){REDUCE, 29};
	at[29][10] = (t_table){REDUCE, 29};
	at[30][0] = (t_table){REDUCE, 27};
	at[30][1] = (t_table){REDUCE, 27};
	at[30][2] = (t_table){REDUCE, 27};
	at[30][4] = (t_table){REDUCE, 27};
	at[30][5] = (t_table){REDUCE, 27};
	at[30][6] = (t_table){REDUCE, 27};
	at[30][7] = (t_table){REDUCE, 27};
	at[30][8] = (t_table){REDUCE, 27};
	at[30][9] = (t_table){REDUCE, 27};
}
