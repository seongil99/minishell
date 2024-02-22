/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:23:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/22 13:02:20 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_env_lst *envlst)
{
	t_env_node	*tmp;
	int	i;
	// char		**args;

	i = 0;
	// args = get_cmd_args(lst); //////////////////////// env 인자 안받게 고
	tmp = envlst->head;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}
