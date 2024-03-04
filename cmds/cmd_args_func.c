/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:56:57 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/03 10:57:03 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*last_args(t_cmd_lst *lst)
{
	char	**args;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	args = get_cmd_args(lst);
	while (args[i])
		i++;
	ret = ft_strdup(args[i - 1]);
	j = 0;
	while (j < i)
		free(args[j++]);
	free(args);
	return (ret);
}

char	**get_cmd_args(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	char		**args;
	int			nums;

	nums = 0;
	tmp = lst->curr;
	while (tmp && is_cmd(tmp))
	{
		nums++;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!is_cmd(tmp))
		tmp = tmp->prev;
	args = (char **)ft_calloc(nums + 1, sizeof(char *));
	args[nums--] = NULL;
	while (nums >= 0 && tmp)
	{
		args[nums--] = ft_strdup(tmp->token);
		tmp = tmp->prev;
	}
	return (args);
}
