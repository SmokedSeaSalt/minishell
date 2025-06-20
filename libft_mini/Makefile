NAME = libft_mini.a
CC = cc -Wall -Werror -Wextra

#	echo_mini.c \
#	pwd_mini.c \
#	export_mini.c \
#	unset_mini.c \
#	env_mini.c \
#	exit_mini.c \

SRCS = \
	cd_mini.c \
	ft_calloc.c \
	ft_env.c \
	ft_exit.c \
	ft_export.c \
	ft_isquote.c \
	ft_isspace.c \
	ft_max.c \
	ft_min.c \
	ft_pwd.c \
	ft_split.c \
	ft_strcmp.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strndup.c \
	skip_to_quote.c \
	strjoin_char.c \
	strjoin_path.c \
	strjoin_space.c

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