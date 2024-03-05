/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:28:48 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/05 09:24:07 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cmd_for_rr(t_cmd_node *node)
{
	if (!node)
		return (0);
	return (node->type == WORD || node->type == LPAR || node->type == RPAR);
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

int	open_file_option(t_cmd_lst *lst)
{
	t_cmd_node	*tmp;
	char		*name;

	tmp = right_redirect_condition(lst);
	name = tmp->token;
	if (tmp->prev->type == GREAT)
		return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (tmp->prev->type == DGREAT)
		return (open(name, O_WRONLY | O_CREAT | O_APPEND, 0666));
	else
	{
		close_pipe(lst);
		exit(g_exit_code);
	}
}

int	get_pl_data_condition(t_cmd_lst *lst)
{
	return (new_get_prev_cmd(lst) || \
	(get_next_cmd_pp(lst)->prev->type == LESS || \
	get_next_cmd_pp(lst)->prev->type == DLESS));
}

void	redi_right(t_cmd_lst *lst, t_env_lst *envlst, char **envp)
{
	int			file;
	char		**args;

	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args_pp(lst);
	if (args[0] == NULL)
		exit(0);
	if (get_pl_data_condition(lst))
		dup2(lst->curr->pipefd[0], STDIN_FILENO);
	file = open_file_option(lst);
	dup2(file, STDOUT_FILENO);
	close_pipe(lst);
	close(file);
	if (!is_builtin(lst))
		exec_program(envlst, args, envp);
	else
		builtin_choice(lst, envlst);
	exit(g_exit_code);
}
