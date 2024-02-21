/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/21 11:14:40 by sihkang          ###   ########seoul.kr  */
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

int	builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;
	int		i;

	i = 1;
	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		{}
	while (args[i])
		put_env_node(envlst, args[i++]);
	return (1);	
}
