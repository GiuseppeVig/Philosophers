NAME = Philosophers
GCC = gcc
FLAGS = -Wall -Werror -Wextra -g -pthread
SRCS = 
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
