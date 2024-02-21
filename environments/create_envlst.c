/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:23:14 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/21 09:59:29 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_equal_separtion(t_env_node *new, char *str)
{
	int		i;
	int		len;

	i = 0;
	if (!str && !new)
		return ;
	while (str[i] != '=')
		i++;
	len = ft_strlen(str);
	new->key = (char *)ft_calloc2(sizeof(char), i + 1);
	new->value = (char *)ft_calloc2(sizeof(char), len - i + 1);
	ft_strlcpy(new->key, str, i + 1);
	ft_strlcpy(new->value, &str[i + 1], len - i + 1);
}

void	create_new_node(t_env_lst *envlst, char *keyval)
{
	t_env_node	*new;
	
	new = (t_env_node *)ft_calloc2(sizeof(t_env_node), 1);
	first_equal_separtion(new, keyval);
	if (envlst->nums == 0)
	{
		envlst->head = new;
		envlst->tail = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		envlst->tail->next = new;
		new->prev = envlst->tail;
		envlst->tail = new;
		new->next = NULL;
	}
	if (!ft_strncmp(new->key, "PWD", 4))
		envlst->pwd = new;
	else if (!ft_strncmp(new->key, "OLDPWD", 7))
		envlst->oldpwd = new;
	else if (!ft_strncmp(new->key, "PATH", 5))
		envlst->path = new;
	envlst->nums++;
}

void	init_env_lst(t_env_lst *envlst, char **envp)
{
	int			i;
	char		*tmp;

	i = 0;
	envlst->nums = 0;
	envlst->oldpwd = 0;
	while (envp[i])
	{
		create_new_node(envlst, envp[i++]);
		if (!ft_strncmp(envlst->tail->key, "PATH", 5))
			envlst->path = envlst->tail;
		else if (!ft_strncmp(envlst->tail->key, "PWD", 4))
			envlst->pwd = envlst->tail;
		else if (!ft_strncmp(envlst->tail->key, "OLDPWD", 7))
			envlst->oldpwd = envlst->tail;
	}
	if (!envlst->oldpwd)
	{
		tmp = ft_strjoin("OLDPWD=",envlst->pwd->value);
		create_new_node(envlst, tmp);
		free(tmp);
	}
	return ;
}
