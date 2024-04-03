# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/19 18:29:26 by kaye              #+#    #+#              #
#    Updated: 2020/08/27 15:04:58 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_cat
FLAGS = -Wall -Wextra -Werror
SRCS = *.c
OBJS = $(SRCS:.c=.o)
HEADERS = ft.h

all :
	@ gcc $(FLAGS) $(SRCS) -c -I $(HEADERS)
	@ gcc $(FLAGS) $(OBJS) -o $(NAME)

clean :
	@ rm -Rf $(OBJS)

fclean : clean
	@ rm -Rf $(NAME)

re : fclean all
