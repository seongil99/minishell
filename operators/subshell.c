/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:29:07 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/21 12:04:00 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_subshell(t_cmd_lst *lst)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		lst->curr = lst->curr->next;
		return ;
	}
	else
	{
		waitpid(id, &g_exit_code, 0);
		move_to_close_subshell(lst);
	}
}

void	move_to_close_subshell(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	int			num_ss;

	num_ss = 1;
	tmp = lst->curr;
	tmp = tmp->next;
	while (tmp && num_ss)
	{
		if (!ft_strncmp(tmp->token, "(", 2))
			num_ss++;
		else if (!ft_strncmp(tmp->token, ")", 2))
			num_ss--;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (!is_cmd(tmp))
			tmp = tmp->next;
		else
			break;
	}
	lst->curr= tmp;
}
