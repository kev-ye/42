# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/19 11:47:35 by kaye              #+#    #+#              #
#    Updated: 2020/08/19 12:54:52 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ./srcs/ft_putchar.c ./srcs/ft_swap.c ./srcs/ft_putstr.c ./srcs/ft_strlen.c ./srcs/ft_strcmp.c

SRCSPATH = ./srcs/ft_putchar.o ./srcs/ft_putstr.o ./srcs/ft_strcmp.o ./srcs/ft_strlen.o ./srcs/ft_swap.o

PATH = ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

FLAGS = -Wall -Wextra -Werror

HEADERS = ./includes/

all : $(NAME)

$(NAME) :
	gcc $(FLAGS) -c -I $(HEADERS) $(SRCS)
	ar -rcs $(NAME) $(PATH)
	mv $(PATH) ./srcs

clean :
	rm -Rf $(SRCSPATH)

fclean : clean
	rm -Rf $(NAME)

re : fclean all
