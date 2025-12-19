NAME	=	philo_bonus

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3

SRCS	=	main_bonus.c \
			init_bonus.c init_utils_bonus.c\
			actions_bonus.c \
			semaphores_bonus.c \
			utils_bonus.c validation_bonus.c monitoring_bonus.c

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
