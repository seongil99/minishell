/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:13:15 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/05 13:13:02 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_io_exec(t_cmd_lst *lst, t_env_lst *envlst, \
						char **envp, pid_t *proc_id)
{
	if (is_builtin(lst) && (!new_get_prev_cmd(lst) && !get_next_cmd_pp(lst)))
		builtin_choice(lst, envlst);
	else
	{
		if (is_logical(lst->curr))
			logic_control(lst, envlst, envp, proc_id);
		else
		{
			*proc_id = fork2();
			if (*proc_id == 0)
			{
				if (left_redirect_condition(lst))
					redi_left(lst);
				else if (new_get_prev_cmd(lst))
					dup2(lst->curr->pipefd[0], STDIN_FILENO);
				if (right_condition(lst))
					redi_right(lst, envlst, envp);
				else
					pipe_exec(lst, envlst, envp);
			}
		}
	}
}

void	start_cmd(t_cmd_lst *lst, t_env_lst *envlst, \
				char **envp, int *proc_id)
{
	process_io_exec(lst, envlst, envp, proc_id);
	move_to_next_cmd(lst);
}

void	run_commands(t_cmd_lst *lst, t_env_lst *envlst, \
					char **envp, struct termios org_term)
{
	int			proc_id;

	proc_id = 0;
	cmd_pre_process(lst, envlst);
	if (g_exit_code == 0)
	{
		while (lst->curr)
		{
			if (lst->curr->type == RPAR || lst->curr->type == LPAR || \
			align_pl_location_condition(lst->curr))
			{
				lst->curr = lst->curr->next;
				continue ;
			}
			set_program_envir(lst, envlst, org_term);
			start_cmd(lst, envlst, envp, &proc_id);
		}
		cmd_post_process(lst, proc_id);
	}
}
