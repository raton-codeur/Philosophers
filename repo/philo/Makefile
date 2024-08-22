NAME = philo
FLAGS = -Wall -Werror -Wextra -I inc -g3 #-fsanitize=address
OBJS = $(patsubst src/%, tmp/%, $(SRCS:.c=.o))
SRCS = \
	src/check_args.c \
	src/free.c \
	src/init.c \
	src/utils.c \
	src/check_simulation_stop.c \
	src/threads.c \
	src/philo.c \
	src/routine.c \
	src/routine_utils.c \

tmp/%.o : src/%.c
	@ mkdir -p $(dir $@)
	@ cc $(FLAGS) -c $< -o $@ && printf "."

$(NAME) : $(OBJS)
	@ cc $(FLAGS) $^ -o $@ && printf "\n"

all : $(NAME)

clean :
	@ rm -rf tmp && printf "cleaned\n"

fclean : clean
	@ rm -f $(NAME) && printf "deleted\n"

re : fclean all

.PHONY : all clean fclean re