/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:28:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 13:10:11 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_for_rr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type != PIPE);
}

t_cmd_node	*get_prev_cmd_rr(t_cmd_lst *lst)
{
	t_cmd_node	*ret;

	if (lst->curr == lst->head)
		return (NULL);
	ret = lst->curr->prev;
	while (ret && !is_cmd_for_rr(ret))
		ret = ret->prev;
	if (ret && (ret->type == AND_IF || ret->type == OR_IF))
		return (NULL);
	while (ret && is_cmd_for_rr(ret))
	{
		if (ret == lst->head && ret->type == WORD)
			return (ret);
		else if (ret->type != WORD)
			return (NULL);
		ret = ret->prev;
	}
	if (!ret)
		return (NULL);
	return (ret->next);
}

int	open_file_option(t_cmd_node *tmp)
{
	char	*name;

	name = tmp->next->token;
	if (tmp->type == GREAT)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (tmp->type == DGREAT)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0666));
	else
		exit(g_exit_code);
}

int	get_pl_data_condition(t_cmd_lst *lst)
{
	return (get_prev_cmd_rr(lst) && \
	(get_next_cmd_pp(lst)->prev->type == LESS || \
	get_next_cmd_pp(lst)->prev->type == DLESS));
}

void	redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int			file;
	char		**args;
	t_cmd_node	*tmp;

	if (logic_stop(lst))
		exit(g_exit_code);
	tmp = lst->curr;
	printf("hihihihi\n");
	while (tmp->next && \
		tmp->type != DGREAT && \
		tmp->type != GREAT)
		tmp = tmp->next;
	args = get_cmd_args_pp(lst);
	if (get_pl_data_condition(lst))
		dup2(lst->curr->pipefd[0], STDIN_FILENO);
	file = open_file_option(tmp);
	dup2(file, STDOUT_FILENO);
	close_pipe(lst);
	close(file);
	if (!builtin_choice(lst, envlst))
	{
		exec_program(envlst, args, envp);
		perror("minishell right redirection");
	}
	exit(g_exit_code);
}
