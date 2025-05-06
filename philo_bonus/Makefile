NAME	=	philo_bonus

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	main_bonus.c utils_bonus.c libft_funcs_bonus.c

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