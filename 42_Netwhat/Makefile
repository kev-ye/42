# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/05 17:33:11 by kaye              #+#    #+#              #
#    Updated: 2020/12/07 02:03:41 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation

CC = clang
IFLAGS = -I./inc

# DIRECTORIES

OBJ_DIR	:= .obj
SRC_DIR := src
DIRS	:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SRC_DIR))

# File

NAME := netwhat_helper_v1.2

SUB_SRC := main.c \
	  	   get_ip_number.c \
	  	   get_part_mask.c \
	  	   get_cidr.c \
	  	   address_prive.c \
	  	   address_public.c \
	  	   calcul_ip_with_mask.c \
	  	   calcul_mask.c \
	  	   get_range_ip.c \
	  	   init_ip.c \
		   model_osi.c
SRC		:= $(addprefix $(SRC_DIR)/, $(SUB_SRC))
OBJ 	:= $(SRC:%.c=$(OBJ_DIR)/%.o)

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

# Makefile

$(NAME): $(OBJ)
		@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
		@$(CC) $(IFLAGS) $^ -o $(NAME)
		@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

$(OBJ_DIR):
		@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
		@mkdir $(DIRS)
		
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
		@echo "Compiling $(MAGENTA_COLOR)$< $(DEFAULT_COLOR)..."
		@$(CC) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re