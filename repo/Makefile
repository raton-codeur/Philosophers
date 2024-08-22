NAME = philo
FLAGS = -Wall -Werror -Wextra -I inc -g3 -fsanitize=address
SRCS = $(shell find src -type f -name "*.c")
OBJS = $(patsubst src/%, tmp/%, $(SRCS:.c=.o))

tmp/%.o : src/%.c
	@ mkdir -p $(dir $@)
	@ cc $(FLAGS) -c $< -o $@ && printf ".\n"

$(NAME) : $(OBJS)
	@ cc $(FLAGS) $^ -o $@ && printf "\n"

all : $(NAME)

clean :
	@ rm -rf tmp && printf "cleaned\n"

fclean : clean
	@ rm -f $(NAME) && printf "deleted\n"

re : fclean all

.PHONY : all clean fclean re

test :
	@ make --no-print-directory
	./philo 2 1000 200 100