/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:43 by sihkang           #+#    #+#             */
/*   Updated: 2024/03/04 18:08:36 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	argu_cleaner(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	if (args)
		free(args);
}

void	cd_post_process(t_env_lst *envlst, char **args)
{
	update_pwd(envlst);
	argu_cleaner(args);
}

void	dir_access_test_no_args(t_env_lst *envlst)
{
	if (!envlst->n_home || !envlst->n_home->value)
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else if (envlst->n_home && access(envlst->n_home->value, F_OK))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	}
	else
	{
		g_exit_code = 0;
		chdir(envlst->n_home->value);
	}
}

void	dir_access_test_args(char **args)
{
	if (access(args[1], F_OK))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	}
	else if (access(args[1], R_OK))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: Permission denied\n", 2);
	}
	else
	{
		g_exit_code = 0;
		chdir(args[1]);
	}
}

int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;

	args = get_cmd_args(lst);
	update_oldpwd(envlst);
	if (args[0] && !args[1])
		dir_access_test_no_args(envlst);
	else if (args[1])
		dir_access_test_args(args);
	cd_post_process(envlst, args);
	return (1);
}
