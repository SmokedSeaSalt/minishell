NAME = minishell
CC = cc #-Wall -Werror -Wextra

LIBFT_MINI_PATH = libft_mini
LIBFT_MINI = ./libft_mini/libft_mini.a

LIBFT_MINI_INCL = -I libft_mini/inc
INCL = -I inc $(LIBFT_MINI_INCL)

BUILD_FOLDER = build

BUILTIN_SRCS = 	src/built_in/cd_mini.c \
				src/built_in/echo_mini.c \
				src/built_in/env_mini.c \
				src/built_in/exit_mini.c \
				src/built_in/export_mini.c \
				src/built_in/pwd_mini.c \
				src/built_in/unset_mini.c

BUILTIN_OBJS := $(patsubst src/built_in/%.c, $(BUILD_FOLDER)/%.o, $(BUILTIN_SRCS))

SRCS =			src/cmds_list.c \
				src/error_parse_line.c \
				src/executor.c \
				src/main.c \
				src/parsing.c \
				src/signals.c

OBJS := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRCS))

ALL_OBJS = $(BUILTIN_OBJS) $(OBJS)


all: libft_mini $(NAME)

$(NAME): $(ALL_OBJS) $(LIBFT_MINI) Makefile
	$(CC) -lreadline $(ALL_OBJS) $(LIBFT_MINI) $(INCL) -o $(NAME)

$(BUILD_FOLDER)/%.o: src/built_in/%.c Makefile | $(BUILD_FOLDER)
	$(CC) $(INCL) -c -o $@ $<

$(BUILD_FOLDER)/%.o: src/%.c Makefile | $(BUILD_FOLDER)
	$(CC) $(INCL) -c -o $@ $<

$(BUILD_FOLDER):
	mkdir -p $@

libft_mini:
	make -C $(LIBFT_MINI_PATH)

clean:
	make -C $(LIBFT_MINI_PATH) clean
	rm -rf $(BUILD_FOLDER)

fclean: clean
	make -C $(LIBFT_MINI_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft_mini