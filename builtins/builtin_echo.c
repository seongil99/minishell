/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 19:57:58 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_option_check(t_cmd_node *arg)
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

static void	write_echo_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return ;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	builtin_echo(t_cmd_lst *lst)
{
	int		skip;
	char	**args;

	lst->curr = lst->curr->next;
	skip = echo_option_check(lst->curr);
	if (skip)
	{
		while (skip--)
			lst->curr = lst->curr->next;
		args = get_cmd_args_pp(lst);
		write_echo_args(args);
	}
	else
	{
		args = get_cmd_args_pp(lst);
		write_echo_args(args);
		write(1, "\n", 1);
	}
	g_exit_code = 0;
	argu_cleaner(args);
	return (1);
}
