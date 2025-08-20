NAME = libft_mini.a
CC = cc -Wall -Werror -Wextra

SRCS = \
		charinstr.c \
		ft_calloc.c \
		ft_isquote.c \
		ft_isspace.c \
		ft_max.c \
		ft_memmove.c \
		ft_min.c \
		ft_realloc.c \
		ft_split.c \
		ft_strcmp.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strndup.c \
		init_env.c \
		is_only_num.c \
		is_valid_in_name.c \
		n_args.c \
		skip_to_quote.c \
		strjoin_char.c \
		strjoin_path.c \
		strjoin_space.c \
		#update_env.c

BUILD_FOLDER = build
OBJS := $(patsubst %.c, $(BUILD_FOLDER)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) Makefile
	ar rcsUu $(NAME) $(ALLOBJS)

$(BUILD_FOLDER)/%.o: %.c Makefile | $(BUILD_FOLDER)
	$(CC) -c -o $@ $<

$(BUILD_FOLDER):
	mkdir -p $@

clean:
	rm -rf $(BUILD_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re