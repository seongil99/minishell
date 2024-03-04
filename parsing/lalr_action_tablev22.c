/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_action_tablev22.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:08:58 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 20:11:05 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

void	_init_action_table10(t_table **at)
{
	at[30][10] = (t_table){REDUCE, 27};
	at[31][0] = (t_table){REDUCE, 28};
	at[31][1] = (t_table){REDUCE, 28};
	at[31][2] = (t_table){REDUCE, 28};
	at[31][4] = (t_table){REDUCE, 28};
	at[31][5] = (t_table){REDUCE, 28};
	at[31][6] = (t_table){REDUCE, 28};
	at[31][7] = (t_table){REDUCE, 28};
	at[31][8] = (t_table){REDUCE, 28};
	at[31][9] = (t_table){REDUCE, 28};
	at[31][10] = (t_table){REDUCE, 28};
	at[32][0] = (t_table){REDUCE, 30};
	at[32][1] = (t_table){REDUCE, 30};
	at[32][2] = (t_table){REDUCE, 30};
	at[32][4] = (t_table){REDUCE, 30};
	at[32][5] = (t_table){REDUCE, 30};
	at[32][6] = (t_table){REDUCE, 30};
	at[32][7] = (t_table){REDUCE, 30};
	at[32][8] = (t_table){REDUCE, 30};
	at[32][9] = (t_table){REDUCE, 30};
	at[32][10] = (t_table){REDUCE, 30};
	at[33][0] = (t_table){REDUCE, 31};
	at[33][1] = (t_table){REDUCE, 31};
	at[33][2] = (t_table){REDUCE, 31};
	at[33][4] = (t_table){REDUCE, 31};
}

void	_init_action_table11(t_table **at)
{
	at[33][5] = (t_table){REDUCE, 31};
	at[33][6] = (t_table){REDUCE, 31};
	at[33][7] = (t_table){REDUCE, 31};
	at[33][8] = (t_table){REDUCE, 31};
	at[33][9] = (t_table){REDUCE, 31};
	at[33][10] = (t_table){REDUCE, 31};
	at[34][0] = (t_table){REDUCE, 2};
	at[34][1] = (t_table){REDUCE, 2};
	at[34][2] = (t_table){SHIFT, 19};
	at[34][4] = (t_table){REDUCE, 2};
	at[34][10] = (t_table){REDUCE, 2};
	at[35][0] = (t_table){REDUCE, 3};
	at[35][1] = (t_table){REDUCE, 3};
	at[35][2] = (t_table){SHIFT, 19};
	at[35][4] = (t_table){REDUCE, 3};
	at[35][10] = (t_table){REDUCE, 3};
	at[36][0] = (t_table){REDUCE, 5};
	at[36][1] = (t_table){REDUCE, 5};
	at[36][2] = (t_table){REDUCE, 5};
	at[36][4] = (t_table){REDUCE, 5};
	at[36][10] = (t_table){REDUCE, 5};
	at[37][0] = (t_table){REDUCE, 23};
	at[37][1] = (t_table){REDUCE, 23};
	at[37][2] = (t_table){REDUCE, 23};
	at[37][4] = (t_table){REDUCE, 23};
}

void	_init_action_table12(t_table **at)
{
	at[37][6] = (t_table){REDUCE, 23};
	at[37][7] = (t_table){REDUCE, 23};
	at[37][8] = (t_table){REDUCE, 23};
	at[37][9] = (t_table){REDUCE, 23};
	at[37][10] = (t_table){REDUCE, 23};
	at[38][0] = (t_table){REDUCE, 10};
	at[38][1] = (t_table){REDUCE, 10};
	at[38][2] = (t_table){REDUCE, 10};
	at[38][4] = (t_table){REDUCE, 10};
	at[38][5] = (t_table){SHIFT, 40};
	at[38][6] = (t_table){SHIFT, 13};
	at[38][7] = (t_table){SHIFT, 14};
	at[38][8] = (t_table){SHIFT, 15};
	at[38][9] = (t_table){SHIFT, 16};
	at[38][10] = (t_table){REDUCE, 10};
	at[39][0] = (t_table){REDUCE, 19};
	at[39][1] = (t_table){REDUCE, 19};
	at[39][2] = (t_table){REDUCE, 19};
	at[39][4] = (t_table){REDUCE, 19};
	at[39][5] = (t_table){REDUCE, 19};
	at[39][6] = (t_table){REDUCE, 19};
	at[39][7] = (t_table){REDUCE, 19};
	at[39][8] = (t_table){REDUCE, 19};
	at[39][9] = (t_table){REDUCE, 19};
	at[39][10] = (t_table){REDUCE, 19};
}

void	_init_action_table13(t_table **at)
{
	at[40][0] = (t_table){REDUCE, 21};
	at[40][1] = (t_table){REDUCE, 21};
	at[40][2] = (t_table){REDUCE, 21};
	at[40][4] = (t_table){REDUCE, 21};
	at[40][5] = (t_table){REDUCE, 21};
	at[40][6] = (t_table){REDUCE, 21};
	at[40][7] = (t_table){REDUCE, 21};
	at[40][8] = (t_table){REDUCE, 21};
	at[40][9] = (t_table){REDUCE, 21};
	at[40][10] = (t_table){REDUCE, 21};
	at[41][0] = (t_table){REDUCE, 9};
	at[41][1] = (t_table){REDUCE, 9};
	at[41][2] = (t_table){REDUCE, 9};
	at[41][4] = (t_table){REDUCE, 9};
	at[41][6] = (t_table){REDUCE, 9};
	at[41][7] = (t_table){REDUCE, 9};
	at[41][8] = (t_table){REDUCE, 9};
	at[41][9] = (t_table){REDUCE, 9};
	at[41][10] = (t_table){REDUCE, 9};
}
