/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalr_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonyoon <seonyoon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:38:41 by seonyoon          #+#    #+#             */
/*   Updated: 2024/02/14 13:29:48 by seonyoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALR_PARSER_H
# define LALR_PARSER_H

# include "../utils/mini_utils.h"
# include "../libft/libft.h"

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
	WORD,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	PIPE,
	LESS,
	GREAT,
	LPAR,
	RPAR,
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

#endif
