/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:23:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/23 11:17:03 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_env_node	*tmp;
	int			i;

	i = 0;
	if (is_cmd(lst->curr->next))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: env: No options in env\n", STDERR_FILENO);
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
