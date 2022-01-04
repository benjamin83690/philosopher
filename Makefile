CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
HEADER	= include
SRCS	= srcs/philosopher.c
RM		= rm -f
NAME	= philosopher

OBJS 	= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $@ $^ $(CFLAGS) -I$(HEADER)

clean:
	$(RM) srcs/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re
