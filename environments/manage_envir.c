/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:29:36 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/16 12:13:30 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_node(t_env_lst *envlst, char *delkey)
{
	t_env_node	*tmp;

	tmp = search_env_node(envlst, delkey);
	printf("key : %s | value : %s\n", tmp->key, tmp->value);
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	envlst->nums--;
}

void	put_env_node(t_env_lst *envlst, char *str)
{
	t_env_node	*tmp;
	int			i;
	int			len;
	char		*findkey;

	i = 0;
	while (str[i] != '=')
			i++;
	len = ft_strlen(str);
	findkey = ft_calloc2(sizeof(char), i + 1);
	ft_strlcpy(findkey, str, i + 1);
	tmp = search_env_node(envlst, findkey);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = (char *)ft_calloc2(sizeof(char), len - i + 1);
		ft_strlcpy(tmp->value, &str[i + 1], len - i + 1);
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