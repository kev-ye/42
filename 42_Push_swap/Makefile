# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 18:48:36 by kaye              #+#    #+#              #
#    Updated: 2021/03/28 16:45:37 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror
LFLAGS	= -L./libft -lft
IFLAGS 	= -I./libft/inc -I./inc

# DIRECTORIES

BUILD 			:= .build
INC_DIR 		:= inc
SRC_DIR 		:= src
SUB_DIR			:= checker \
				   push_swap \
				   common
LFT_DIR			:= libft
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

PUSH_SWAP		:= push_swap
CHECKER			:= checker
SRC				:= push_swap.c \
				   do_op.c \
				   five_less.c \
				   hundred.c \
				   sort_algo.c
SRC_PUSH_SWAP	:= $(addprefix push_swap/, $(SRC))
SRC				:= action.c \
				   checker.c
SRC_CHECKER		:= $(addprefix checker/, $(SRC))
SRC				:= free.c \
				   op_p.c \
				   op_r.c \
				   op_rr.c \
				   op_s.c \
				   parser.c \
				   utils.c \
				   option.c
SRC_COMMON		:= $(addprefix common/, $(SRC))
OBJ_PUSH_SWAP	:= $(SRC_PUSH_SWAP:%.c=$(OBJ_DIR)/%.o)
OBJ_CHECKER		:= $(SRC_CHECKER:%.c=$(OBJ_DIR)/%.o)
OBJ_COMMON		:= $(SRC_COMMON:%.c=$(OBJ_DIR)/%.o)

# COLORS

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m

# MAKEFILE

$(PUSH_SWAP): $(OBJ_PUSH_SWAP) $(OBJ_CHECKER) $(OBJ_COMMON)
	@$(MAKE) -C $(LFT_DIR)
	@echo "Creating $(RED_COLOR) $(PUSH_SWAP) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_COMMON) $(OBJ_PUSH_SWAP) $(IFLAGS) $(LFLAGS) -o $(PUSH_SWAP)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(PUSH_SWAP) $(BLUE_COLOR)done$(DEFAULT_COLOR)"
	@echo "Creating $(RED_COLOR) $(CHECKER) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_COMMON) $(OBJ_CHECKER) $(IFLAGS) $(LFLAGS) -o $(CHECKER)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(CHECKER) $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(PUSH_SWAP)

clean:
	@$(MAKE) -C $(LFT_DIR) clean
	rm -Rf $(BUILD)
fclean: clean
	@$(MAKE) -C $(LFT_DIR) fclean
	rm -Rf push_swap
	rm -Rf checker

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS);

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@
