NAME = rush-02
FLAGS = -Wall -Wextra -Werror
HEADERS = rush_02.h
SRCS = *.c
OBJS = $(SRCS:.c=.o)

all :
	@ gcc $(FLAGS) $(SRCS) -c
	@ gcc $(FLAGS) $(OBJS) -o $(NAME) -I $(HEADERS)

clean :
	@ rm -Rf $(OBJS)

fclean : clean
	@ rm -Rf $(NAME)

re : fclean all