NAME = philo
FLAGS = -Wall -Wextra -Werror

SRCS = philo.c \
		utils.c \
		check_arguments.c \




OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re