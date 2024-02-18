/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:41:09 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:34:31 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*tilde_expansion(char *str, char *home_dir)
{
	char	*ret;

	if (!str || !home_dir)
		return (NULL);
	if (str[0] != '~' || str[1] != '/' || str[1] != '\0')
		ret = ft_strdup(str);
	else
		ret = ft_strjoin(home_dir, str + 1);
	return (ret);
}
