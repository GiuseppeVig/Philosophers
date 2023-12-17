NAME = philo
GCC = gcc
FLAGS = -Wall -Werror -Wextra -g -pthread
SRCS = philo_func.c philo_utils.c routines.c philosophers.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME):
	$(GCC) $(FLAGS) $(SRCS) -c
	$(GCC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
