NAME = libft_mini.a
CC = cc -Wall -Werror -Wextra

#	pwd_mini.c \
#	export_mini.c \
#	unset_mini.c \
#	env_mini.c \
#	exit_mini.c \

SRCS = \
	echo_mini.c \
	cd_mini.c \
	ft_calloc.c \
	ft_isquote.c \
	ft_isspace.c \
	ft_max.c \
	ft_min.c \
	ft_split.c \
	ft_strcmp.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strndup.c \
	skip_to_quote.c \
	strjoin_char.c \
	strjoin_path.c \
	strjoin_space.c \
	expand_env.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	ar rcsUu $(NAME) $(ALLOBJS)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re