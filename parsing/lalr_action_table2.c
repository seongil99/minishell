/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_table2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:43:29 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/17 20:48:13 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_act_init5(t_table **at)
{
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
}

void	_act_init6(t_table **at)
{
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
}

void	_act_init7(t_table **at)
{
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
}

void	_act_init8(t_table **at)
{
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
}

void	_act_init9(t_table **at)
{
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
}
