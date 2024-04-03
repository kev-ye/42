# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/20 16:53:01 by kaye              #+#    #+#              #
#    Updated: 2020/08/21 13:37:56 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = do-op
SRCS = *.c
OBJS = $(SRCS:.c=.o)
HEADERS = ft_do_op.h
FLAGS = -Wall -Wextra -Werror

all :
	@ gcc $(FLAGS) $(SRCS) -c
	@ gcc $(FLAGS) $(OBJS) -o $(NAME) -I $(HEADERS)

clean :
	@ rm -Rf $(OBJS)

fclean : clean
	@ rm -Rf $(NAME)

re : fclean all

