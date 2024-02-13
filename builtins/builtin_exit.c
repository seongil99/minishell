/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:01:34 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/12 19:20:06 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(const char c)
{
	return (
		c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' '
	);
}

static long long	ft_atoll(const char *str)
{
	long long	ret;
	long long	sign;

	ret = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (sign * ret);
}

void	builtin_exit(t_lst	*lst)
{
	int	i;

	i = 0;
	if (lst->nums > 2)
	{
		perror("too many arguments");
		g_exit_code = 1;
	}
	if (lst->nums == 2)
	{
		while (lst->curr->next->token[i])
		{
			if (!ft_isalpha(lst->curr->next->token[i++]))
			{
				perror("numeric argument required");
				g_exit_code = 255;
			}
		}
		g_exit_code = ft_atoll(lst->curr->next->token) % 256;
		if (g_exit_code < 0)
			g_exit_code += 256;
	}
	else
		g_exit_code = 0;
	exit(g_exit_code);
}
