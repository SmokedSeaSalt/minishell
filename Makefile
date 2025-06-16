SRCS = pipex_utils.c main.c here_doc.c
LIBFTPATH = libft
BSRCS = 
NAME = pipex

ifdef WITHBONUS
OBJS = $(BSRCS:.c=.o)
else
OBJS = $(SRCS:.c=.o)
endif

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

LIBFT = -L$(LIBFTPATH) -lft

all:			$(NAME)

$(NAME): $(LIBFTPATH)/libft.a $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFTPATH)/libft.a:
				make -C $(LIBFTPATH)

clean:
				$(RM) $(OBJS) $(BSRCS:.c=.o)
				make clean -C $(LIBFTPATH)


fclean:			clean
				$(RM) $(NAME)
				$(RM) checker
				make fclean -C $(LIBFTPATH)

re:				fclean $(NAME)

bonus:
				$(MAKE) WITHBONUS=1 all

.PHONY:			all clean fclean re bonus