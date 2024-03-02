/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:52:34 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/02 16:25:28 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_choice(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (logic_stop(lst))
		return (1);
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (builtin_env(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (builtin_unset(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "export", 7))
		return (builtin_export(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "echo", 5))
		return (builtin_echo(lst));
	else if (!ft_strncmp(lst->curr->token, "cd", 3))
		return (builtin_cd(lst, envlst));
	else if (!ft_strncmp(lst->curr->token, "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(lst->curr->token, "exit", 5))
		builtin_exit(lst);
	return (0);
}

int	is_builtin(t_cmd_lst *lst)
{
	if (!ft_strncmp(lst->curr->token, "env", 4))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "unset", 6))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "export", 7))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "echo", 5))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "cd", 3))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "pwd", 4))
		return (1);
	else if (!ft_strncmp(lst->curr->token, "exit", 5))
		return (1);
	return (0);
}
