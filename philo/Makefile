NAME = philo
FLAGS = -Wall -Wextra -Werror -g

SRCS = philo.c \
		check_arguments.c \
		init.c \
		protect.c \
		time.c \
		monitor.c \
		finishing.c \
		eating.c \
		routine.c \




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