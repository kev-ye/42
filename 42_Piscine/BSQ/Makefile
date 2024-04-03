# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wiozsert <wiozsert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 11:06:28 by wiozsert          #+#    #+#              #
#    Updated: 2020/08/26 17:59:56 by wiozsert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq
FLAGS = -Wall -Werror -Wextra
FILESC = ./srcs/*.c
FILESO = *.o
FILESOPATH = ./srcs/*.o
HEADER = -I ./includes/

all : $(NAME)

$(NAME) :
	gcc $(FLAGS) -c $(FILESC) $(HEADER)
	gcc $(FLAGS) $(FILESO) -o $(NAME)
	mv $(FILESO) ./srcs/

clean :
	rm -f ./srcs/*.o

fclean : clean
	rm -f $(NAME)

re : fclean all
