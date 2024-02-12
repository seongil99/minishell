/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:23:34 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/12 17:52:38 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PARSING_H
# define MINI_PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include "scanner.h"
# include "../libft/libft.h"
# include "../utils/ft_stack.h"
# include "../utils/mini_utils.h"

# define WORD 1
# define AND_IF 2
# define OR_IF 3
# define DLESS 4
# define DGREAT 5

typedef enum e_parse_type
{
	COMMAND,
	AND_AND,
	OR_OR,
	PIPE,
	IO_REDIRECT,
	IO_APPEND,
	IO_INPUT,
	IO_HEREDOC,
	FILENAME,
	SUBSHELL,
	HERE_END
}	t_parse_type;

typedef struct s_treenode
{
	t_token				*data;
	int					children_size;
	struct s_treenode	*children;
}	t_treenode;

typedef struct s_automata
{
	t_token	*input;
	t_stack	stack;
}	t_automata;

#endif
