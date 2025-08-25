# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 15:57:58 by mvan-rij          #+#    #+#              #
#    Updated: 2025/08/25 16:13:04 by mvan-rij         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_mini.a
CC = cc -Wall -Werror -Wextra -I ../inc -I inc

SRCS = \
		src/charinstr.c \
		src/free_carray.c \
		src/ft_calloc.c \
		src/ft_isquote.c \
		src/ft_isspace.c \
		src/ft_max.c \
		src/ft_memmove.c \
		src/ft_min.c \
		src/ft_realloc.c \
		src/ft_split.c \
		src/ft_strcmp.c \
		src/ft_strjoin.c \
		src/ft_strlen.c \
		src/ft_strncmp.c \
		src/ft_strndup.c \
		src/init_env.c \
		src/is_only_num.c \
		src/is_valid_in_name.c \
		src/n_args.c \
		src/strjoin_char.c \
		src/strjoin_path.c \
		src/strjoin_space.c \
		src/update_env.c

INCLS = \
	inc/libft_mini.h

BUILD_FOLDER = build
OBJS := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) Makefile $(INCLS)
	ar rcsUu $(NAME) $(OBJS)

$(BUILD_FOLDER)/%.o: src/%.c Makefile $(INCLS) | $(BUILD_FOLDER)
	$(CC) -c -o $@ $<

$(BUILD_FOLDER):
	mkdir -p $@

clean:
	rm -rf $(BUILD_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re