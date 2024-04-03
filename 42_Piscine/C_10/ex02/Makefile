# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 12:38:18 by kaye              #+#    #+#              #
#    Updated: 2020/08/24 12:26:52 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_tail
FLAGS = -Wall -Wextra -Werror
SRCS = *.c
OBJS = $(SRCS:.c=.o)
HEADERS = ft.h

all :
	@ gcc $(FLAGS) $(SRCS) -c
	@ gcc $(FLAGS) $(OBJS) -o $(NAME) -I $(HEADERS)

clean :
	@ rm -Rf $(OBJS)

fclean : clean
	@ rm -Rf $(NAME)

re : fclean all
