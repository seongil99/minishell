/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:58:13 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:18:12 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_parsing.h"

t_gmr_var	get_char_type(t_scanner *src, char c)
{
	if (c == '(')
		return (LPAR);
	else if (c == ')')
		return (RPAR);
	else if (c == '|' && peek_char(src) == '|')
		return (OR_IF);
	else if (c == '|')
		return (PIPE);
	else if (c == '&' && peek_char(src) == '&')
		return (AND_IF);
	else if (c == '<' && peek_char(src) == '<')
		return (DLESS);
	else if (c == '<')
		return (LESS);
	else if (c == '>' && peek_char(src) == '>')
		return (DGREAT);
	else if (c == '>')
		return (GREAT);
	return (WORD);
}

char	token_add_char(t_scanner *src, t_token *tkn, t_buf *buf)
{
	char	c;

	c = next_char(src);
	if (c == ' ' || c == '\t')
		return (0);
	if (tkn->type && tkn->type != get_char_type(src, c))
	{
		cur_back(src);
		return (0);
	}
	buf_add_char(buf, c);
	if (tkn->type == 0)
		tkn->type = get_char_type(src, c);
	if (tkn->type == DLESS || tkn->type == DGREAT
		|| tkn->type == OR_IF || tkn->type == AND_IF)
	{
		buf_add_char(buf, next_char(src));
		return (0);
	}
	else if (tkn->type != WORD)
		return (0);
	return (c);
}

t_token	*get_next_token(t_scanner *src)
{
	t_token			*tkn;
	t_buf			*buf;

	tkn = ft_calloc2(1, sizeof(t_token));
	buf = buf_new();
	skip_whitespaces(src);
	while (peek_char(src) != T_EOF)
	{
		if (!token_add_char(src, tkn, buf))
			break ;
	}
	tkn->str_len = ft_strlen(buf->buf);
	if (tkn->str_len == 0)
	{
		buf_del(buf);
		free(tkn);
		return (NULL);
	}
	tkn->str = buf_get_str(buf);
	buf_del(buf);
	return (tkn);
}

t_token	*token_dup(t_token *org)
{
	t_token	*ret;

	ret = ft_calloc2(1, sizeof(t_token));
	ret->str = ft_strdup(org->str);
	if (!ret->str)
		exit_err("MEM Error\n");
	ret->str_len = org->str_len;
	ret->type = org->type;
	return (ret);
}

t_lst	*tokenize(char *command)
{
	t_scanner	*src;
	t_token		*temp;
	t_lst		*head;

	head = NULL;
	src = scanner_new(command);
	while (true)
	{
		temp = get_next_token(src);
		if (!temp)
			break ;
		lst_push_back(&head, lst_new(temp));
	}
	scanner_del(src);
	return (head);
}
