/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:23:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/14 08:40:26 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_env_lst *envlst)
{
	t_env_node	*tmp;
	int	i;

	i = 0;
	tmp = envlst->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
