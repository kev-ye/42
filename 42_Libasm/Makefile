# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/10 17:29:25 by kaye              #+#    #+#              #
#    Updated: 2021/05/14 22:02:07 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

NA		= nasm
ifeq ($(shell uname), Darwin)
	NAFLAG	= -f macho64
else ifeq ($(shell uname), Linux)
	NAFLAG	= -f elf64 -D __LINUX__
endif
CC			= clang
CFLAG		= -Wall -Wextra -Werror
IFLAG		= -I./inc
D_MANDATORY	= -D __MANDATORY__
D_BONUS		= -D __BONUS__

# DIRECTORIES

BUILD		:= .build
INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= $(BUILD)/obj
DIR			:= $(OBJ_DIR)

# FILES

NAME		:= libasm.a
MAIN		:= main_test_exec
MAIN_BONUS	:= main_test_exec_bonus
MAIN_SRC	:= main.c
SRC			:= ft_strlen.s \
			   ft_strcpy.s \
			   ft_strcmp.s \
			   ft_write.s \
			   ft_read.s \
			   ft_strdup.s \
			   ft_list_size_bonus.s \
			   ft_list_push_front_bonus.s
OBJ			:= $(SRC:%.s=$(OBJ_DIR)/%.o)

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
	@echo "Creating $(RED_COLOR) $@ $(DEFAULT_COLOR)..."
	@ar -rcs $@ $^
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

$(MAIN): $(NAME)
	@$(CC) $(CFLAG) $(IFLAG) $(D_MANDATORY) $(MAIN_SRC) $(NAME) -o $@
	@./$(MAIN) 2>/dev/null

$(MAIN_BONUS): $(NAME)
	@$(CC) $(CFLAG) $(IFLAG) $(D_BONUS) $(MAIN_SRC) $(NAME) -o $@
	@./$(MAIN_BONUS) 2>/dev/null

all: $(NAME)

bonus: all

test: $(MAIN)

test_bonus: $(MAIN_BONUS)

clean:
	rm -Rf $(BUILD)

fclean: clean
	rm -Rf $(NAME)
	rm -Rf $(MAIN)
	rm -Rf $(MAIN_BONUS)

re: fclean all

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(NA) $(NAFLAG) $< -o $@

.PHONY : all clean fclean re