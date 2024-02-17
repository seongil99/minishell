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

PARSE_SRC		= lalr_goto.c \
				lalr_parsing.c \
				lalr_reduce.c \
				lalr_shift.c \
				lalr_table.c \
				scanner.c \
				scanner_func.c \
				tokenize.c

UTILS_SRC		= ft_calloc2.c \
				ft_stack.c \
				linked_list_push.c \
				linked_list.c \
				utils.c

MAIN_SRC		= test.c

SRCS			= $(MAIN_SRC) \
				$(addprefix $(PARSE_DIR)/,$(PARSE_SRC)) \
				$(addprefix $(UTILS_DIR)/,$(UTILS_SRC))
OBJS			= $(SRCS:.c=.o)
INCLUDES		= minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAG) $(READLINE_FLAG) -o $(NAME)

$(OBJS): $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(UTILS_DIR) -I$(PARSE_DIR) $(READLINE_INCLUDE) -c $< -o $@

clean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all bonus clean fclean re
