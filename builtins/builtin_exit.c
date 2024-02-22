/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:01:34 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/22 08:30:17 by sihkang          ###   ########seoul.kr  */
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
	if (*str == '-')
		sign = -1;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - '0');
		str++;
		digits++;
		if (digits > 19)
		{
			perror("numeric argument required");
			exit(255);
		}
	}
	return (sign * ret);
}

void	builtin_exit(t_cmd_lst	*lst)
{
	int		i;
	char	**args;

	i = 0;
	args = get_cmd_args(lst);
	if (args[1] && args[2])
	{
		perror("too many arguments");
		g_exit_code = 1;
		return ;
	}
	else if (args[1] && !args[2])
	{
		while (args[1][i])
		{
			if (ft_isalpha(args[1][i++]))
			{
				perror("numeric argument required");
				exit(255);
			}
		}
		g_exit_code = ft_atoll(args[1]) % 256;
		if (g_exit_code < 0)
			g_exit_code += 256;
	}
	else if (args[0] && !args[1])
		g_exit_code = 0;
	exit(g_exit_code);
}
