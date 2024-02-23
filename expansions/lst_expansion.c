/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihkang <sihkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:38:02 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/23 18:50:21 by sihkang          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	lst_tilde_expansion(t_lst *tknlst, t_env_lst *envlst)
{
	t_token	*token;
	char	*home_dir;

	home_dir = get_home_dir(envlst);
	if (!home_dir)
		return ;
	while (tknlst)
	{
		token = tknlst->data;
		replace_str(&(token->str), tilde_expansion(token->str, home_dir));
		tknlst = tknlst->next;
	}
}

void	lst_param_expansion(t_lst *tknlst, t_env_lst *envlst)
{
	t_token	*token;

	while (tknlst)
	{
		token = tknlst->data;
		replace_str(&(token->str), param_expansion(token->str, envlst, false));
		tknlst = tknlst->next;
	}
}

void	lst_path_expansion(t_lst **head)
{
	t_lst	*temp;
	t_lst	*tknlst;

	tknlst = *head;
	while (tknlst)
	{
		temp = tknlst->next;
		path_expansion(head, tknlst);
		tknlst = temp;
	}
}

void	lst_quote_removal(t_lst *tknlst)
{
	t_token	*token;

	while (tknlst)
	{
		token = tknlst->data;
		replace_str(&(token->str), quote_removal(token->str));
		tknlst = tknlst->next;
	}
}
