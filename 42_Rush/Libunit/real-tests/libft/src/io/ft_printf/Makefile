# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/25 22:45:37 by kaye              #+#    #+#              #
#    Updated: 2022/01/09 13:40:22 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror
IFLAGS 		= -I./inc -I../../../inc

# DIRECTORIES

INC_DIR	 	:= inc
SRC_DIR  	:= src
SUB_DIR		:= printf_family
OBJ_DIR	 	:= .obj
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

NONE			= \033[0m
CL_LINE			= \033[2K
B_BLACK			= \033[1;30m
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_YELLOW		= \033[1;33m
B_BLUE			= \033[1;34m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

# MAKEFILE

$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@ar -rcs $@ $^

all: $(NAME)

bonus: all

clean:
	@rm -Rf $(OBJ_DIR)

fclean: clean
	@rm -Rf $(NAME)

re: fclean all

$(OBJ_DIR):
	@mkdir $(DIRS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@printf "$(CL_LINE)Compiling srcs object : $(B_MAGENTA)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re
