# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/13 02:01:30 by besellem          #+#    #+#              #
#    Updated: 2021/06/10 22:43:05 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a

## Main directories
BUILD_DIR	:=	.build
SRCS_DIR	:=	srcs
INCS		:=	-I incs
SUB_DIR		:=	ctype \
				list \
				math \
				stdio \
				stdlib \
				string
OBJ_DIR 	:=	$(BUILD_DIR)/obj
DIRS		:=	$(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


## Main srcs
# ctype
SUB_SRCS	:=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_iscntrl.c \
				ft_isdigit.c \
				ft_isgraph.c \
				ft_islower.c \
				ft_isprint.c \
				ft_ispunct.c \
				ft_isspace.c \
				ft_isupper.c \
				ft_isxdigit.c \
				ft_tolower.c \
				ft_toupper.c
SRCS		:=	$(addprefix ctype/, $(SUB_SRCS))

# list
SUB_SRCS	:=	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c
SRCS		+=	$(addprefix list/, $(SUB_SRCS))

# math
SUB_SRCS	:=	ft_abs.c \
				ft_ceil.c \
				ft_copysign.c \
				ft_factorial.c \
				ft_fdim.c \
				ft_find_next_prime.c \
				ft_floor.c \
				ft_fma.c \
				ft_fmax.c \
				ft_fmin.c \
				ft_fmod.c \
				ft_gcd.c \
				ft_frexp.c \
				ft_hypot.c \
				ft_isinf.c \
				ft_isnan.c \
				ft_isprime.c \
				ft_ldexp.c \
				ft_lround.c \
				ft_modf.c \
				ft_pow.c \
				ft_round.c \
				ft_signbit.c \
				ft_sqrt.c \
				ft_trunc.c
SRCS		+=	$(addprefix math/, $(SUB_SRCS))

# stdio
SUB_SRCS	:=	ft_putaddr_fd.c \
				ft_putaddr.c \
				ft_putc_fd.c \
				ft_putc.c \
				ft_putchar_fd.c \
				ft_putchar.c \
				ft_putendl_fd.c \
				ft_putendl.c \
				ft_putn_fd.c \
				ft_putn.c \
				ft_putnbr_fd.c \
				ft_putnbr.c \
				ft_putnstr_fd.c \
				ft_putnstr.c \
				ft_putstr_fd.c \
				ft_putstr.c \
				get_next_line.c
SRCS		+=	$(addprefix stdio/, $(SUB_SRCS))

# printf
PRINTF_SRCS	=	$(SRCS_DIR)/stdio/ft_printf/*/*.c

# stdlib
SUB_SRCS	:=	ft_atod.c \
				ft_atoi_base.c \
				ft_atoi.c \
				ft_atol.c \
				ft_atold.c \
				ft_atoll.c \
				ft_calloc.c \
				ft_itoa_base.c \
				ft_itoa.c \
				ft_nblen_base.c \
				ft_nblen.c \
				ft_random.c \
				ft_strtol.c \
				ft_strtoll.c
SRCS		+=	$(addprefix stdlib/, $(SUB_SRCS))

# string
SUB_SRCS	:=	ft_bcmp.c \
				ft_bcopy.c \
				ft_bzero.c \
				ft_incharset.c \
				ft_index.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memdel.c \
				ft_memmove.c \
				ft_memset.c \
				ft_rindex.c \
				ft_split.c \
				ft_strcapitalize.c \
				ft_strcasestr.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_stridx.c \
				ft_strisall.c \
				ft_strisalnum.c \
				ft_strisalpha.c \
				ft_strisascii.c \
				ft_strisdigit.c \
				ft_strisprint.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strlowcase.c \
				ft_strmapi.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strndup.c \
				ft_strnlen.c \
				ft_strnstr.c \
				ft_stroc.c \
				ft_strpbrk.c \
				ft_strrchr.c \
				ft_strsfree.c \
				ft_strsjoin.c \
				ft_strslen.c \
				ft_strsplit.c \
				ft_strstr.c \
				ft_strtrim.c \
				ft_strupcase.c \
				ft_substr.c \
				ft_trn.c \
				ft_trni.c \
				ft_trnu.c
SRCS		+=	$(addprefix string/, $(SUB_SRCS))


## Objects
PRINTF_OBJS	:=	$(PRINTF_SRCS:.c=.o)
OBJS 		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)


## Commands
CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror
LIBC		:=	ar rc
RM			:=	rm -f


# Colors
CLR_COLOR	:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m


## Compilation
$(NAME):	$(OBJS)
			@ echo "Compiling $(RED)ft_printf $(CLR_COLOR)..."
			@ $(MAKE) -C $(SRCS_DIR)/stdio/ft_printf >/dev/null
			@ echo "Creating $(RED)$(NAME) $(CLR_COLOR)..."
			@ $(LIBC) $(NAME) $(OBJS) $(PRINTF_OBJS)
			@ echo "$(GREEN)Compilation $(YELLOW)of $(RED)$@ $(BLUE)done$(CLR_COLOR)"

all:		$(NAME)

bonus:		all

clean:
			@ echo "Deleting $(CYAN)libft's $(CLR_COLOR)objs ..."
			@ $(MAKE) -C $(SRCS_DIR)/stdio/ft_printf clean >/dev/null
			@ $(RM) $(OBJS)
			@ rm -rf $(BUILD_DIR)

fclean:		clean
			@ echo "Deleting $(CYAN)libft $(CLR_COLOR)library ..."
			@ $(MAKE) -C $(SRCS_DIR)/stdio/ft_printf fclean >/dev/null
			@ $(RM) $(NAME)

re:			fclean all

$(BUILD_DIR):
			@ echo "Creating $(RED)$@ $(CLR_COLOR)..."
			@ mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRCS_DIR)/%.c | $(BUILD_DIR)
			@ echo "Compiling $(YELLOW)$< $(CLR_COLOR)..."
			@ $(CC) $(CFLAGS) -c $< -o $@ $(INCS)
# @ $(CC) $(CFLAGS) -c $< -o $@ $(INCS) -D LIBC_NO_CRASH_ON_NULL=0

.PHONY:		all bonus clean fclean re
