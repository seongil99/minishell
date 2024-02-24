/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:30:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 18:46:18 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

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
		action_table = ft_calloc2(42, sizeof(t_table *));
		i = 0;
		while (i < 42)
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
		goto_table = ft_calloc2(42, sizeof(t_table *));
		i = 0;
		while (i < 42)
		{
			goto_table[i] = ft_calloc2(15, sizeof(t_table));
			i++;
		}
	}
	return (goto_table);
}
