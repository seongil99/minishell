/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/21 12:32:41 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;
	int		i;

	i = 1;
	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		return (1);
	while (args[i])
		remove_env_node(envlst, args[i++]);
	return (1);
}

void	print_declared_env(t_env_lst *envlst)
{
	t_env_node	*tmp;

	tmp = envlst->head;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}

int	builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;
	int		i;

	i = 1;
	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		print_declared_env(envlst);
	while (args[i])
	{
		put_env_node(envlst, args[i++]);
	}
	return (1);	
}
