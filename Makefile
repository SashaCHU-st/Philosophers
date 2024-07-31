NAME = philo
FLAGS = -Wall -Wextra -Werror

SRCS = philo.c \


OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	make clean -C
	rm -f $(OBJS)

fclean: clean
	make fclean -C
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re