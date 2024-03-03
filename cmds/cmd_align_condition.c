/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_align_condition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:01:50 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 15:53:30 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd_node	*left_redirect_condition(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	t_cmd_node	*ret;

	tmp = lst->curr;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == AND_IF || tmp->type == OR_IF)
			return (ret);
		else if (tmp->type == LESS || tmp->type == DLESS)
		{
			ret = tmp->next;
			if (tmp->type == LESS && access(ret->token, F_OK | R_OK))
			{
				perror("minishell");
				exit(1);
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	right_redirect_condition(t_cmd_lst *lst)
{
	return (get_next_cmd_after_lr(lst) && \
	(get_next_cmd_after_lr(lst)->prev->type == GREAT || \
	get_next_cmd_after_lr(lst)->prev->type == DGREAT));
}

int	align_pl_location_condition(t_cmd_node *curr)
{
	return (curr->type != WORD && \
			curr->type != LESS && \
			curr->type != DLESS && \
			curr->type != GREAT && \
			curr->type != DGREAT);
}
