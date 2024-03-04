/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:29:36 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/27 14:04:48 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	special_variable_remove(t_env_lst *envlst, char *delkey)
{
	if (envlst->pwd && \
	!ft_strncmp(delkey, envlst->pwd->key, ft_strlen(delkey) + 1))
		envlst->pwd = 0;
	else if (envlst->oldpwd && \
	!ft_strncmp(delkey, envlst->oldpwd->key, ft_strlen(delkey) + 1))
		envlst->oldpwd = 0;
	else if (envlst->path && \
	!ft_strncmp(delkey, envlst->path->key, ft_strlen(delkey) + 1))
		envlst->path = 0;
	else if (envlst->n_home && \
	!ft_strncmp(delkey, envlst->n_home->key, ft_strlen(delkey) + 1))
		envlst->n_home = 0;
	else if (envlst->underbar && \
	!ft_strncmp(delkey, envlst->underbar->key, ft_strlen(delkey) + 1))
		envlst->underbar = 0;
}

void	remove_env_node(t_env_lst *envlst, char *delkey)
{
	t_env_node	*tmp;

	tmp = search_env_node(envlst, delkey);
	if (!tmp)
		return ;
	if (tmp == envlst->head)
		envlst->head = tmp->next;
	if (tmp == envlst->tail)
		envlst->tail = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	special_variable_remove(envlst, delkey);
	free(tmp->key);
	tmp->key = 0;
	free(tmp->value);
	tmp->value = 0;
	free(tmp);
	tmp = 0;
	envlst->nums--;
	g_exit_code = 0;
}

void	value_setting(t_env_node *tmp, char *str, int len, int i)
{
	if (len == i)
		tmp->value = NULL;
	else
	{
		tmp->value = (char *)ft_calloc2(sizeof(char), len - i + 1);
		ft_strlcpy(tmp->value, &str[i + 1], len - i + 1);
	}
}

void	put_env_node(t_env_lst *envlst, char *str)
{
	t_env_node	*tmp;
	int			i;
	int			len;
	char		*findkey;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	len = ft_strlen(str);
	findkey = ft_calloc2(sizeof(char), i + 1);
	ft_strlcpy(findkey, str, i + 1);
	tmp = search_env_node(envlst, findkey);
	if (tmp)
	{
		free(tmp->value);
		value_setting(tmp, str, len, i);
	}
	else
		create_new_node(envlst, str);
	free(findkey);
	findkey = 0;
	return ;
}

t_env_node	*search_env_node(t_env_lst *envlst, char *findkey)
{
	t_env_node	*tmp;
	int			len;

	len = ft_strlen(findkey) + 1;
	tmp = envlst->head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, findkey, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
