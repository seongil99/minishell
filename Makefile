CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LIBFT_FLAG		= -L./libft -lft
READLINE_FLAG	= -L/usr/local/include/readline -lreadline -lhistory

NAME			= minishell

LIBFT_DIR		= ./libft
PARSE_DIR		= ./parsing
UTILS_DIR		= ./utils
BUILT_DIR		= ./builtins
TMSIG_DIR		= ./termi_signal
ENVIR_DIR		= ./environments
OPERA_DIR		= ./operators
EXPNS_DIR		= ./expansions
COMDS_DIR		= ./cmds

COMDS_SRC		= init_rm_cmds.c \
				manage_cmd.c \
				pipe_func.c \
				run_commands.c \
				convert_cmd.c \
				cmd_args_func.c \
				cmd_checker.c \
				get_next_cmds_func.c \
				cmd_reordering.c \
				exec_program.c \
				cmd_align_condition.c \
				get_prev_cmd_func.c

EXPNS_SRC		= lst_expansion.c \
				param_expansion.c \
				pathname_expansion_bonus.c \
				pattern_match_bonus.c \
				quote_removal.c \
				tilde_expansion.c \
				utils.c \
				word_expansion.c

EXPNS_INCLUDE	= expansions.h

PARSE_SRC		= lalr_action_tablev2.c \
				lalr_action_tablev21.c \
				lalr_action_tablev22.c \
				lalr_automata.c \
				lalr_goto_tablev2.c \
				lalr_goto.c \
				lalr_parsing.c \
				lalr_reduce.c \
				lalr_shift.c \
				lalr_table.c \
				quote_check.c \
				scanner.c \
				scanner_func.c \
				token.c \
				tokenize.c

PARSE_INCLUDE	= lalr_parser.h \
				lalr_table.h \
				mini_parsing.h \
				parsing_type.h \
				scanner.h

UTILS_SRC		= ft_calloc2.c \
				ft_stack.c \
				ft_stack_func.c \
				linked_list_push.c \
				linked_list.c \
				str_buffer.c \
				str_buffer2.c \
				utils.c \
				get_next_line.c

UTILS_INCLUDE	= ft_stack.h \
				linked_list.h \
				mini_utils.h \
				str_buffer.h

BUILT_SRC		= builtin_dir.c \
				builtin_pwd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_unset_export.c \
				builtin_select.c

TMSIG_SRC		= signal_control.c \
				terminal_mode.c

ENVIR_SRC		= create_envlst.c \
				manage_envir.c

OPERA_SRC		= heredoc_utils.c \
				heredoc.c \
				right_redirection.c \
				left_redirection.c \
				subshell_bonus.c \
				logics_bonus.c

MAIN_SRC		= main.c

SRCS			= $(MAIN_SRC) \
				$(addprefix $(EXPNS_DIR)/,$(EXPNS_SRC)) \
				$(addprefix $(PARSE_DIR)/,$(PARSE_SRC)) \
				$(addprefix $(UTILS_DIR)/,$(UTILS_SRC)) \
				$(addprefix $(BUILT_DIR)/,$(BUILT_SRC)) \
				$(addprefix $(TMSIG_DIR)/,$(TMSIG_SRC)) \
				$(addprefix $(ENVIR_DIR)/,$(ENVIR_SRC)) \
				$(addprefix $(OPERA_DIR)/,$(OPERA_SRC)) \
				$(addprefix $(COMDS_DIR)/,$(COMDS_SRC))

OBJS			= $(SRCS:.c=.o)
INCLUDES		= minishell.h \
				envir.h \
				$(addprefix $(EXPNS_DIR)/,$(EXPNS_INCLUDE)) \
				$(addprefix $(PARSE_DIR)/,$(PARSE_INCLUDE)) \
				$(addprefix $(UTILS_DIR)/,$(UTILS_INCLUDE)) \

bonus: all
all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAG) $(READLINE_FLAG) -o $(NAME)

$(OBJS): $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(EXPNS_DIR) -I$(UTILS_DIR) -I$(PARSE_DIR) -I$(BUILT_DIR) -I$(TMSIG_DIR) -I$(ENVIR_DIR) -I$(OPERA_DIR) -I$(COMDS_DIR) $(READLINE_INCLUDE) -c $< -o $@

clean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all bonus clean fclean re
