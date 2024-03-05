/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:40:32 by seonyoon          #+#    #+#             */
/*   Updated: 2024/03/05 12:35:23 by seonyoon         ###   ########.fr       */
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

typedef struct s_quote_info
{
	char	c;
	int		idx;
	int		flag;
}	t_quote_info;

int		word_expantion(t_lst **tknlst, t_env_lst *envlst);
void	lst_tilde_expansion(t_lst *tknlst, t_env_lst *envlst);
void	lst_param_expansion(t_lst *tknlst, t_env_lst *envlst);
int		lst_path_expansion(t_lst **tknlst);
void	lst_quote_removal(t_lst *tknlst);
char	*quote_removal(char *str);
char	*param_expansion(char *str, t_env_lst *elst, bool is_heredoc);
char	*tilde_expansion(char *str, char *home_dir);
int		path_expansion(t_lst **head, t_lst *tknnode, t_lst *prev);
char	*get_home_dir(t_env_lst *envlst);
void	replace_str(char **dist, char *new_str);
void	set_quote_flag(int *flag, char c, char *str);

#endif
