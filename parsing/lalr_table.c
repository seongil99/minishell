/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/14 13:33:35 by seonyoon         ###   ########.fr       */
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
	static t_table	goto_table[14][37];

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

void	init_goto_table(void)
{
	t_table	**gt;

	gt = get_goto_table();
	ft_memset(gt, 0, sizeof(t_table) * 14 * 37);
}
