/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/15 19:31:49 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_option_check(t_node *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg->token[i++] == '-')
	{
		while (arg->token[i])
		{
			if (arg->token[i] == 'n')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1 + echo_option_check(arg->next));
}

static void	write_echo_args(t_lst *lst)
{
	if (!lst->curr)
		return ;
	while (lst->curr->next && is_op(lst->curr->next))
	{
		write(1, lst->curr->token, ft_strlen(lst->curr->token));
		write(1, " ", 1);
		lst->curr = lst->curr->next;
	}
	write(1, lst->curr->token, ft_strlen(lst->curr->token));
}

int	builtin_echo(t_lst *lst)
{
	int	skip;

	lst->curr = lst->curr->next;
	skip = echo_option_check(lst->curr);
	if (skip)
	{
		while (skip--)
			lst->curr = lst->curr->next;
		write_echo_args(lst);
	}
	else
	{
		write_echo_args(lst);
		write(1, "\n", 1);
	}
	return (1);
}
