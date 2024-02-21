/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:28:34 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/20 19:26:38 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static int	special_variable(t_buf *buf)
{
	int		temp;
	char	*exit_code;

	temp = g_exit_code;
	exit_code = ft_itoa(temp);
	buf_add_str(buf, exit_code);
	free(exit_code);
	return (2);
}

static int	insert_variable(char *str, t_buf *buf, t_env_lst *elst)
{
	t_env_node	*node;
	char		*end;
	char		temp;

	temp = 0;
	end = str;
	while (*end)
	{
		if (!ft_isalnum(*end))
		{
			temp = *end;
			break ;
		}
		end++;
	}
	*end = '\0';
	node = search_env_node(elst, str);
	if (node)
		buf_add_str(buf, node->value);
	*end = temp;
	return (end - str + 1);
}

static int	append_param(char *str, t_buf *buf, t_env_lst *elst, int flag)
{
	int	ret;

	ret = 0;
	if (flag != SQUOTE && *str == '$')
	{
		str++;
		if (*str == '?')
			ret += special_variable(buf);
		else if (ft_isalnum(*str))
			ret += insert_variable(str, buf, elst);
		else
		{
			buf_add_char(buf, '$');
			buf_add_char(buf, *str);
			ret++;
		}
	}
	else
	{
		buf_add_char(buf, *str);
		ret++;
	}
	return (ret);
}

char	*param_expansion(char *str, t_env_lst *elst)
{
	t_buf	*buf;
	char	*ret;
	int		flag;

	if (!str || !elst)
		return (NULL);
	buf = buf_new();
	flag = NO_QUOTE;
	while (*str)
	{
		set_quote_flag(&flag, *str);
		str += append_param(str, buf, elst, flag);
	}
	ret = buf_get_str(buf);
	buf_del(buf);
	return (ret);
}
