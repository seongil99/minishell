CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_FLAGS	= -Llibft -lft

NAME		= minishell

SRCS		= main.c
OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= ./libft

all: $(NAME)

$(NAME): $(OBJS)
	make all -sC $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

$(OBJS): minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -I. -Ilibft -c $< -o $@

clean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(OBJS)

fclean:
	make fclean -sC $(LIBFT_DIR)
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all bonus clean fclean re
