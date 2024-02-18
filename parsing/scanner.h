/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:16:00 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 15:41:33 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "../libft/libft.h"
# include "../utils/mini_utils.h"
# include "mini_parsing.h"

t_scanner	*scanner_new(char *line);
void		scanner_del(t_scanner *s);
char		next_char(t_scanner *src);
char		peek_char(t_scanner *src);
void		cur_back(t_scanner *src);
void		skip_whitespaces(t_scanner *src);
t_lst		*tokenize(char *command);
t_token		*token_new(char *str, t_gmr_var type);
void		token_del(void *t);
t_token		*token_dup(t_token *org);
t_token		*token_new(char *str, t_gmr_var type);
void		token_del(void *tkn);

#endif
