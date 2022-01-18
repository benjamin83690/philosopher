CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
HEADER	= include
SRCS	= srcs/philosopher.c \
		  srcs/error.c \
		  srcs/routine.c \
		  srcs/time.c
BONUS	= srcs/philosopher_bonus.c \
		  srcs/error_bonus.c \
		  srcs/routine_bonus.c \
		  srcs/time_bonus.c
RM		= rm -f
NAME	= philosopher

ifndef WITH_BONUS
	OBJS 	= $(SRCS:.c=.o)
else
	OBJS 	= $(BONUS:.c=.o)
endif

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $@ $^ $(CFLAGS) -I$(HEADER)

bonus:
		make WITH_BONUS=1 all

clean:
	$(RM) srcs/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re bonus
