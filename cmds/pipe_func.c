/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:29:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/05 12:51:44 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_check(t_cmd_node *tmp)
{
	return (tmp->type == LESS || tmp->type == DLESS || tmp->type == GREAT || \
	tmp->type == DGREAT || tmp->prev->type == LESS || \
	tmp->prev->type == DLESS || tmp->prev->type == GREAT || \
	tmp->prev->type == DGREAT);
}

char	**need_realloc_chk(char **args, int nums, int *size)
{
	if (nums + 1 == *size)
	{
		args = ft_realloc(args, (*size) * sizeof(char *), \
		(*size) * sizeof(char *) * 2);
		(*size) *= 2;
	}
	return (args);
}

char	**push_args(t_cmd_lst *lst, char **args, int *nums, int *size)
{
	t_cmd_node	*tmp;

	tmp = lst->curr->next;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == AND_IF || tmp->type == OR_IF || \
		tmp->type == LPAR || tmp->type == RPAR || tmp->prev->type == LPAR || \
		tmp->prev->type == RPAR)
			break ;
		if (redirect_check(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type != WORD)
			break ;
		args = need_realloc_chk(args, *nums, size);
		args[(*nums)++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	args[*nums] = NULL;
	return (args);
}

char	**get_cmd_args_pp(t_cmd_lst *lst)
{
	char	**args;
	int		nums;
	int		size;

	if (!lst->curr)
		return (NULL);
	size = 10;
	nums = 0;
	args = (char **)ft_calloc(size, sizeof(char *));
	if (lst->curr->type == WORD)
		args[nums++] = ft_strdup(lst->curr->token);
	else if (lst->curr->type == AND_IF || lst->curr->type == OR_IF || \
	lst->curr->type == PIPE)
	{
		args[nums] = NULL;
		return (args);
	}
	args = push_args(lst, args, &nums, &size);
	return (args);
}

void	pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;

	if (logic_stop(lst))
	{
		close_pipe(lst);
		exit(g_exit_code);
	}
	args = get_cmd_args_pp(lst);
	if (args[0] == NULL)
	{
		close_pipe(lst);
		exit(0);
	}
	if (new_get_next_cmd(lst) && new_get_next_cmd(lst)->type == WORD)
		dup2(new_get_next_cmd(lst)->pipefd[1], STDOUT_FILENO);
	close_pipe(lst);
	if (!is_builtin(lst))
		exec_program(envlst, args, envp);
	else
		builtin_choice(lst, envlst);
	exit(g_exit_code);
}
