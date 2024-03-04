/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:01:34 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 16:39:38 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long	ft_atoll(const char *str)
{
	long long	ret;
	long long	sign;
	int			digits;

	digits = 0;
	ret = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = 1 * (44 - *str);
		str++;
	}
	while (1)
	{
		if (!ft_isdigit(*str) || digits > 19)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(255);
		}
		ret = ret * 10 + (*(str++) - '0');
		if (*str == 0)
			break ;
		digits++;
	}
	return (sign * ret);
}

void	convert_ec_uc_range(char *arg)
{
	g_exit_code = ft_atoll(arg) % 256;
	if (g_exit_code < 0)
		g_exit_code += 256;
}

char	**exit_pre_process(t_cmd_lst	*lst)
{
	char	**args;

	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		exit(0);
	return (args);
}

void	builtin_exit(t_cmd_lst	*lst)
{
	int		i;
	char	**args;

	i = 0;
	args = exit_pre_process(lst);
	if (args[1])
	{
		while (args[1][i])
		{
			if (ft_isalpha(args[1][i++]))
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				exit(255);
			}
		}
		convert_ec_uc_range(args[1]);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_code = 1;
		return ;
	}
	exit(g_exit_code);
}
