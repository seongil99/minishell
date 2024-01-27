CC				= cc
CFLAGS			= -Wall -Wextra -Werror
LIBFT_FLAG		= -L./libft -lft
READLINE_FLAG	= -L/usr/local/include/readline -lreadline -lhistory

NAME			= minishell

SRCS			= main.c
OBJS			= $(SRCS:.c=.o)
INCLUDES		= minishell.h

LIBFT_DIR		= ./libft

all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAG) $(READLINE_FLAG) -o $(NAME)

$(OBJS): $(INCLUDES)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

clean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all bonus clean fclean re
