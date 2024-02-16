/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:38:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/16 17:10:49 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_PARSER_H
# define LALR_PARSER_H

# include "../utils/mini_utils.h"
# include "../libft/libft.h"


# include <stdio.h>

# define PARSE_ERR -1

typedef enum e_gmr_var
{
	COMPLETE_COMMAND = 100,
	AND_OR,
	PIPELINE,
	COMMAND,
	SUBSHELL,
	SIMPLE_COMMAND,
	CMD_NAME,
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

int		lalr_shift(t_automata *at, t_table t);
int		lalr_reduce(t_automata *at, t_table t);
int		lalr_goto(t_automata *at, t_table t);
int		parse_line(t_lst *lst);
void	table_clear(void);

#endif
