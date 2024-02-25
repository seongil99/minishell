/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/25 15:45:40 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;
	int		i;
	int		j;

	i = 1;
	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		g_exit_code = 0;
	else
	{
		while (args[i])
		{
			j = 0;
			while (ft_isalnum(args[i][j]) || args[i][j] == '_')
				j++;
			if (!args[i][j])
				remove_env_node(envlst, args[i]);
			else
			{
				g_exit_code = 1;
				ft_putstr_fd("minishell: unset: not a valid identifier\n", 2);
			}
			i++;
		}
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (1);
}

void	print_declared_env(t_env_lst *envlst)
{
	t_env_node	*tmp;

	tmp = envlst->head;
	while (tmp)
	{
		if (tmp->value)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	g_exit_code = 0;
	return ;
}

int	builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;
	int		i;
	int		j;

	i = 1;
	args = get_cmd_args(lst);
	if (args[0] && !args[1])
		print_declared_env(envlst);
	while (args[i])
	{
		j = 0;
		while (ft_isalnum(args[i][j]) || args[i][j] == '_' || \
		args[i][j] == '=' || args[i][j] == '\"' || \
		args[i][j] == '\'' || args[i][j] == ' ' || args[i][j] == '/')
			j++;
		if (args[i][j] || args[i][0] == '=')
		{
			g_exit_code = 1;
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		}
		else if (!args[i][j])
			put_env_node(envlst, args[i]);
		i++;
	}
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	return (1);
}
