/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/16 11:03:56 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_env_lst *envlst, char *delkey)
{
	remove_env_node(envlst, delkey);
	return (1);
}

int	builtin_export(t_env_lst *envlst, char *keyvalue)
{
	put_env_node(envlst, keyvalue);
	return (1);	
}
