/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:23:03 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 18:09:25 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_env_node	*tmp;
	int			i;

	i = 0;
	if (is_cmd(lst->curr->next))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: env: No options in env\n", STDERR_FILENO);
		return (g_exit_code);
	}
	tmp = envlst->head;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_exit_code = 0;
	return (1);
}

void	update_underbar(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (!get_prev_cmd_rr(lst) && !get_next_cmd_pp(lst))
	{
		if (envlst->underbar)
		{
			free(envlst->underbar->value);
			envlst->underbar->value = 0;
			envlst->underbar->value = last_args(lst);
		}
	}
	else
	{
		free(envlst->underbar->value);
		envlst->underbar->value = 0;
		envlst->underbar->value = ft_strdup("");
	}
}

void	update_oldpwd(t_env_lst *envlst)
{
	if (envlst->oldpwd)
	{
		free(envlst->oldpwd->value);
		envlst->oldpwd->value = get_pwd();
	}
}

void	update_pwd(t_env_lst *envlst)
{
	if (envlst->pwd)
	{
		free(envlst->pwd->value);
		envlst->pwd->value = get_pwd();
	}	
}
