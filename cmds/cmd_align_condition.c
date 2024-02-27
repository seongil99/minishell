/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_align_condition.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:01:50 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 13:09:59 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	left_redirect_condition(t_cmd_lst *lst)
{
	return (get_next_cmd_pp(lst) && \
	(get_next_cmd_pp(lst)->prev->type == LESS || \
	get_next_cmd_pp(lst)->prev->type == DLESS));
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
			curr->type != DLESS);
}
