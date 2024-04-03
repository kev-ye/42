# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/19 18:06:47 by kaye              #+#    #+#              #
#    Updated: 2020/08/27 15:05:42 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file
FLAGS = -Wall -Wextra -Werror
SRCS = ft_display_file.c
OBJS = $(SRCS:.c=.o)

$(NAME) :
	@ gcc $(FLAGS) -c $(SRCS)
	@ gcc $(FLAGS) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	@ rm -rf $(OBJS)

fclean : clean
	@ rm -rf $(NAME)
