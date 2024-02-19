/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:29:07 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/19 10:43:05 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_subshell(t_cmd_lst *lst)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{ 
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
	while (tmp || num_ss)
	{
		if (!ft_strncmp(tmp->token, "(", 2))
			num_ss++;
		else if (!ft_strncmp(tmp->token, ")", 2))
			num_ss--;
		tmp = tmp->next;
	}
	lst->curr= tmp;	
}