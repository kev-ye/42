# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 22:45:37 by kaye              #+#    #+#              #
#    Updated: 2021/03/28 19:46:14 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror
IFLAGS 		= -I./inc_pf -I../../../inc

# DIRECTORIES

INC_DIR	 	:= inc_pf
SRC_DIR  	:= src_pf
SUB_DIR		:= printf_family
OBJ_DIR	 	:= .obj_pf
DIRS		:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SRC_DIR)) \
			   $(addprefix $(OBJ_DIR)/$(SRC_DIR)/, $(SUB_DIR))

# FILES

NAME 		:= libftprintf.a
SUB_SRC 	:= ft_convert_utils.c \
			   ft_convert.c \
			   ft_parse_char.c \
			   ft_parse_check.c \
			   ft_parse_flag_plus.c \
			   ft_parse_flag.c \
			   ft_parse_hex.c \
			   ft_parse_int_p.c \
			   ft_parse_int.c \
			   ft_parse_octal.c \
			   ft_parse_pointer.c \
			   ft_parse_spec.c \
			   ft_parse_string.c \
			   ft_parse_uint.c \
			   ft_parse.c \
			   ft_process.c \
			   ft_utils_pf.c
SRC			:= $(addprefix $(SRC_DIR)/, $(SUB_SRC))
SUB_SRC		:= ft_vprintf.c
SRC			+= $(addprefix $(SRC_DIR)/printf_family/, $(SUB_SRC))
OBJ			:= $(SRC:%.c=$(OBJ_DIR)/%.o)


# COLORS

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m
WHITE_COLOR 	= \033[1;107m

# MAKEFILE

$(NAME): $(OBJ)
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@ar -rcs $@ $^
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

bonus: all

clean:
	rm -Rf $(OBJ_DIR)

fclean: clean
	rm -Rf $(NAME)

re: fclean all

$(OBJ_DIR):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $(DIRS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $(MAGENTA_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re