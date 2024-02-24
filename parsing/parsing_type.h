/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:52:22 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/24 18:25:24 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TYPE_H
# define PARSING_TYPE_H

# include "../utils/mini_utils.h"

# define T_EOF -1
# define PARSE_ERR -1
# define REJECT 0
# define ACC 1
# define SHIFT 2
# define REDUCE 3
# define GOTO 4

typedef struct s_scanner
{
	char	*line;
	int		size;
	int		cur;
}	t_scanner;

typedef enum e_gmr_var
{
	COMPLETE_COMMAND = 100,
	AND_OR,
	PIPELINE,
	COMMAND,
	SUBSHELL,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECTION_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	AND_IF,
	OR_IF,
	PIPE,
	LPAR,
	RPAR,
	WORD,
	LESS,
	GREAT,
	DGREAT,
	DLESS,
	TYPE_EOF
}	t_gmr_var;

typedef struct s_token
{
	t_gmr_var		type;
	int				str_len;
	char			*str;
}	t_token;

typedef struct s_automata
{
	t_lst	*head;
	t_stack	*stack;
}	t_automata;

typedef struct s_table
{
	int	action;
	int	number;
}	t_table;

#endif
