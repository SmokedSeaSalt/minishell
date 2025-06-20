NAME = minishell
CC = cc -Wall -Werror -Wextra

LIBFT_MINI = ./libft_mini/libft_mini.a
LIBFT_MINI_INCL = -I ./libft_mini

SRCS = \


OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT_MINI) $(LIBFT_MINI_INCL) -o $(NAME)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re