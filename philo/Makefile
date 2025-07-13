NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3

SRCS	=	main.c init.c utils.c init_utils.c validation.c actions.c action_utils.c monitoring.c

OBJS	=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re