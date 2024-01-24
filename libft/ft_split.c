/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:51:47 by seonyoon          #+#    #+#             */
/*   Updated: 2023/12/25 13:50:37 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	split_clear(char **l, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(*(l + i));
		i++;
	}
	free(l);
}

size_t	word_len(char const *s, char c)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
	{
		if (s[len] == c)
			break ;
		len++;
	}
	return (len);
}

size_t	worlds_cnt(char const *s, char c)
{
	int		flag;
	size_t	cnt;

	if (!s)
		return (0);
	flag = 1;
	cnt = 0;
	while (*s)
	{
		if (flag && *s != c)
		{
			cnt++;
			flag = 0;
		}
		else if (*s == c)
		{
			flag = 1;
		}
		s++;
	}
	return (cnt);
}

int	append_split(char **ret, char const *s, char c)
{
	size_t	len;
	char	*temp;

	len = word_len(s, c);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, s, len + 1);
	*(ret) = temp;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	len;
	size_t	cnt;
	size_t	i;

	cnt = worlds_cnt(s, c);
	ret = (char **)ft_calloc((cnt + 1), sizeof(char *));
	if (!ret)
		return (0);
	i = 0;
	while (i < cnt)
	{
		while (*s && (*s == c))
			s++;
		len = append_split(ret + i, s, c);
		if (!len)
		{
			split_clear(ret, i);
			return (0);
		}
		s += len;
		i++;
	}
	ret[cnt] = 0;
	return (ret);
}
