/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:57:43 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/23 12:51:41 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;

	args = get_cmd_args(lst);
	update_oldpwd(envlst);
	if (args[0] && !args[1])
	{
		if (chdir(getenv("HOME"))) // 수정필요 envlst에서 HOME을 찾도록.
		{
			perror("minishell chdir 1");
			g_exit_code = 1;
		}
	}
	else if (args[2] || (args[1] && chdir(args[1]))) // 권한체크 필요
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	}
	update_pwd(envlst);
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
