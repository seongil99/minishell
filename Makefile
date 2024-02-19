CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g #-fsanitize=address
LIBFT_FLAG		= -L./libft -lft
READLINE_FLAG	= -L/usr/local/include/readline -lreadline -lhistory
# READLINE_FLAG	= -L/opt/homebrew/opt/readline/lib -lreadline -lhistory
# READLINE_INCLUDE= -I/opt/homebrew/opt/readline/include

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
				convert_cmd.c

EXPNS_SRC		= param_expansion.c \
				pathname_expansion.c \
				quote_removal.c \
				tilde_expansion.c

PARSE_SRC		= lalr_action_table.c \
				lalr_action_table2.c \
				lalr_action_table3.c \
				lalr_automata.c \
				lalr_goto_table.c \
				lalr_goto.c \
				lalr_parsing.c \
				lalr_reduce.c \
				lalr_shift.c \
				lalr_table.c \
				parse_tree.c \
				scanner.c \
				scanner_func.c \
				token.c \
				tokenize.c

UTILS_SRC		= ft_calloc2.c \
				ft_stack.c \
				ft_stack_func.c \
				linked_list_push.c \
				linked_list.c \
				str_buffer.c \
				utils.c \
				get_next_line.c

BUILT_SRC		= builtin_dir.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_unset_export.c

TMSIG_SRC		= signal_control.c

ENVIR_SRC		= create_envlst.c \
				manage_envir.c

OPERA_SRC		= redirection.c \
				subshell.c \
				logics.c

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
INCLUDES		= minishell.h

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
