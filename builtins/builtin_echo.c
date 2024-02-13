/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/12 19:20:02 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_option_check(t_node *arg)
{
	int	i;

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
	return (1);
}

void	builtin_echo(t_lst *lst)
{
	lst->curr = lst->curr->next;
	if (echo_option_check(lst->curr))
	{
		lst->curr = lst->curr->next;
		while (lst->curr && lst->curr != lst->tail)
		{
			printf("%s ", lst->curr->token);
			lst->curr = lst->curr->next;
		}
		printf("%s", lst->curr->token);
	}
	else
	{
		while (lst->curr && lst->curr != lst->tail)
		{
			printf("%s ", lst->curr->token);
			lst->curr = lst->curr->next;
		}
		printf("%s\n", lst->curr->token);
	}	
}
