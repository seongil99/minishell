/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:28:27 by sihkang           #+#    #+#             */
/*   Updated: 2024/02/14 08:50:30 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_lst_del(t_env_node *target)
{
	if (target->prev != NULL)
		target->prev->next = target->next;
	if (target->next != NULL)
		target->next->prev = target->prev;
	free(target->key);
	free(target->value);
	target->key = 0;
	target->value = 0;
	target->next = 0;
	target->prev = 0;
	free(target);
}

static void	remove_env(t_env_lst *envlst, char *remove_key)
{
	t_env_node	*tmp;
	int			len;

	tmp = envlst->head;
	len = ft_strlen(remove_key);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, remove_key, len + 1))
		{
			env_lst_del(tmp);
			break;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_env_lst *envlst, char *remove_key)
{
	remove_env(envlst, remove_key);
	envlst->nums--;
	return (1);
}

void	add_envnode(t_env_lst *envlst, t_env_node *new)
{
	if (envlst->nums == 0)
	{
		envlst->head = new;
		envlst->tail = new;
		envlst->curr = new;
		new->prev = NULL;
	}
	else
	{
		envlst->tail->next = new;
		new->prev = envlst->tail;
		envlst->tail = new;
	}
	new->next = NULL;
	envlst->nums++;
}

int	builtin_export(t_env_lst *envlst, char *keyvalue)
{
	t_env_node	*new;
	t_env_node	*tmp;
	int			len;

	new = (t_env_node *)ft_calloc(sizeof(t_env_node), 1);
	first_equal_separtion(new, keyvalue);
	len = ft_strlen(new->key);
	tmp = envlst->head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, new->key, len + 1))
		{
			tmp->value = new->value;
			free(new->key);
			free(new->value);
			free(new);
			return (1);
		}
		tmp = tmp->next;
	}
	add_envnode(envlst, new);
	return (1);	
}
