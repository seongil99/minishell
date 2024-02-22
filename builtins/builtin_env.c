/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:23:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/22 13:15:52 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_env_node	*tmp;
	int	i;

	i = 0;
	if (is_cmd(lst->curr->next))
	{
		g_exit_code = 1;
		perror("No options in env");
		return (g_exit_code);
	}
	tmp = envlst->head;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
