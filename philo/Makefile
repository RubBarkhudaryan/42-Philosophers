NAME	=	philo

CC		=	cc
CFLAGS	=	-g3  -Wall -Wextra -Werror

SRCS	=	main.c init.c utils.c functions.c validation.c actions.c monitoring.c

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