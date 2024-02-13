/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:43 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/12 19:21:58 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(t_lst *lst)
{
	if (lst->curr->next == 0)
	{
		chdir(getenv("HOME"));
		exit(0);
	}
	if (chdir(lst->curr->next->token))
	{
		g_exit_code = 1;
		perror("minishell chdir");
	}
}

void	builtin_pwd(void)
{
	char 	*tmp;
	size_t	size;

	size = 100;
	tmp = (char *)ft_calloc(sizeof(char), size);
	while (!getcwd(tmp, size))
		size *= 2;
	printf("%s\n", tmp);
	free(tmp);
	g_exit_code = 0;
}