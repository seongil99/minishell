/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 11:17:47 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 14:40:28 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*tmp;
	size_t	size;

	size = 100;
	tmp = (char *)ft_calloc2(sizeof(char), size);
	while (!getcwd(tmp, size))
		size *= 2;
	return (tmp);
}

int	builtin_pwd(void)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_pwd();
	while (tmp[i])
		write(1, &tmp[i++], 1);
	write(1, "\n", 1);
	free(tmp);
	g_exit_code = 0;
	return (1);
}
