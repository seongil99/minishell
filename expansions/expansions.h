/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:40:32 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/20 17:59:15 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "../libft/libft.h"
# include "../utils/mini_utils.h"
# include "../envir.h"
# include "../parsing/mini_parsing.h"

# define NO_QUOTE 0
# define SQUOTE 1
# define DQUOTE 2

extern int	g_exit_code;

t_lst	*word_expantion(t_lst *tknlst, t_env_lst *envlst);
void	lst_tilde_expansion(t_lst *tknlst, t_env_lst *envlst);
void	lst_param_expansion(t_lst *tknlst, t_env_lst *envlst);
void	lst_path_expansion(t_lst *tknlst);
void	lst_quote_removal(t_lst *tknlst);
char	*quote_removal(char *str);
char	*param_expansion(char *str, t_env_lst *elst);
char	*tilde_expansion(char *str, char *home_dir);
void	path_expansion(t_lst *head, t_lst *tknnode);
char	*get_home_dir(t_env_lst *envlst);
void	replace_str(char **dist, char *new_str);
void	set_quote_flag(int *flag, char c);

#endif
