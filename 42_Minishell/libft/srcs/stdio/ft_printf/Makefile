# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/17 21:13:07 by besellem          #+#    #+#              #
#    Updated: 2021/05/19 21:33:51 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MUTE		=	
NAME		=	libftprintf.a

## Mandatory
INCS		=	-I inc -I ../../../incs

SRCS		+=	srcs/ft_common.c \
				srcs/ft_common2.c \
				srcs/ft_common3.c \
				srcs/ft_lst_common.c \
				srcs/ft_lst_common2.c \
				srcs/ft_init_conversions.c \
				srcs/ft_parser.c \
				srcs/ft_specifiers.c \
				srcs/ft_alloc_txt.c \
				srcs/ft_alloc_format.c \
				srcs/ft_format_checks.c \
				srcs/ft_format_checks2.c \
				srcs/ft_alloc_mod.c \
				srcs/ft_alloc_c.c \
				srcs/ft_alloc_s.c \
				srcs/ft_alloc_p.c \
				srcs/ft_alloc_idu.c \
				srcs/ft_alloc_hex.c \
				srcs/ft_alloc_f.c \
				srcs/ft_alloc_f_utils.c \
				srcs/ft_alloc_n.c \
				srcs/ft_alloc_o.c \
				srcs/ft_alloc_b.c

SRCS		+=	family/ft_printf.c \
				family/ft_sprintf.c \
				family/ft_snprintf.c \
				family/ft_asprintf.c \
				family/ft_dprintf.c \
				family/ft_vprintf.c \
				family/ft_vsprintf.c \
				family/ft_vsnprintf.c \
				family/ft_vasprintf.c \
				family/ft_vdprintf.c

## Objects
OBJS		=	$(SRCS:.c=.o)

## Commands
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
LIBC		=	ar rc
RM			=	rm -f

.c.o:
			$(MUTE) $(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCS)

$(NAME):	$(OBJS)
			$(MUTE) $(LIBC) $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(MUTE) $(RM) $(OBJS)

fclean:		clean
			$(MUTE) $(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
