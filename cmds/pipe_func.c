/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:29:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/25 16:25:12 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redirect_check(t_cmd_node *tmp)
{
	return (!ft_strncmp(tmp->token, "<", 1) || \
		!ft_strncmp(tmp->token, ">", 1) || \
		!ft_strncmp(tmp->prev->token, "<", 1) || \
		!ft_strncmp(tmp->prev->token, ">", 1));
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

void	push_args(t_cmd_lst *lst, char **args, int *nums, int *size)
{
	t_cmd_node	*tmp;

	tmp = lst->curr->next;
	while (tmp)
	{
		if (redirect_check(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->type != WORD)
		{
			args[*nums] = NULL;
			break;
		}
		args = need_realloc_chk(args, *nums, size);
		args[(*nums)++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
}

char 	**get_cmd_args_pp(t_cmd_lst *lst)
{
	char	**args;
	int		nums;
	int		size;

	size = 10;
	nums = 0;
	args = (char **)ft_calloc(size, sizeof(char *));
	if (lst->curr->type == WORD)
		args[nums++] = ft_strdup(lst->curr->token);
	push_args(lst, args, &nums, &size);
	return (args);
}

void	pipe_exec(t_cmd_lst *lst, t_env_lst *envlst, char *envp[])
{
	char	**args;
	
	if (logic_stop(lst))
		exit(g_exit_code);
	args = get_cmd_args_pp(lst);
	if (new_get_next_cmd(lst) && new_get_next_cmd(lst)->type == WORD)
		dup2(new_get_next_cmd(lst)->pipefd[1], STDOUT_FILENO);
	close_pipe(lst);
	if (!builtin_choice(lst, envlst))
		exec_program(envlst, args, envp);
	g_exit_code = 1;
}
