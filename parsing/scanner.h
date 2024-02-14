/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:16:00 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/13 16:42:16 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft/libft.h"
# include "../utils/mini_utils.h"
# include "lalr_parser.h"

# define T_EOF -1

typedef struct s_scanner
{
	char	*line;
	int		size;
	int		cur;
}	t_scanner;

typedef struct s_token
{
	t_gmr_var		type;
	int				str_len;
	char			*str;
}	t_token;

typedef struct s_buf
{
	char	*buf;
	int		len;
	int		size;
}	t_buf;

t_scanner	*scanner_new(char *line);
void		scanner_del(t_scanner *s);
char		next_char(t_scanner *src);
char		peek_char(t_scanner *src);
void		cur_back(t_scanner *src);
void		skip_whitespaces(t_scanner *src);
t_lst		*tokenize(char *command);

#endif
