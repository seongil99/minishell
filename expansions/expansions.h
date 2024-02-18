/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:40:32 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/18 19:17:51 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "../libft/libft.h"
# include "../utils/mini_utils.h"
# include "../envir.h"

# define NO_QUOTE 0
# define SQUOTE 1
# define DQUOTE 2

extern int	g_exit_code;

char	*quote_removal(char *str);
char	*param_expansion(char *str, t_env_lst *elst);
char	*tilde_expansion(char *str, char *home_dir);

#endif
