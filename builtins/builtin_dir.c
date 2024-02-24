/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:43 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/24 11:18:58 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;

	args = get_cmd_args(lst);
	update_oldpwd(envlst);
	if (args[0] && !args[1])
	{
		if (!envlst->n_home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_exit_code = 1;
			return (1);
		}
		else if (envlst->n_home && !envlst->n_home->value)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		else if (envlst->n_home && chdir(envlst->n_home->value))
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	}
	else if (args[2] || (args[1] && chdir(args[1])))
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: argument error occured\n", 2);
	}
	update_pwd(envlst);

	int i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	g_exit_code = 0;
	return (1);
}

char	*get_pwd(void)
{
	char	*tmp;
	size_t	size;

	size = 100;
	tmp = (char *)ft_calloc2(sizeof(char), size);
	while (!getcwd(tmp, size))
		size *= 2;
	return (tmp);
}

int	builtin_pwd(void)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_pwd();
	while (tmp[i])
		write(1, &tmp[i++], 1);
	write(1, "\n", 1);
	free(tmp);
	g_exit_code = 0;
	return (1);
}
