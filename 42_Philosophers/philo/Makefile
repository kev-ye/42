# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 14:19:08 by kaye              #+#    #+#              #
#    Updated: 2021/07/14 19:41:19 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror #-g3 -fsanitize=address
IFLAGS 	= -I./incs
LFLAGS	= -lpthread

# DIRECTORIES

BUILD 			:= .build
SRC_DIR 		:= srcs
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR)

# FILES

NAME			:= philo
SRC				:= main.c \
				   philosophers.c \
				   monitor.c \
				   init.c \
				   utils.c \
				   mini_lib.c
OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# COLORS

NONE			= \033[0m
CL_LINE			= \033[2K
S_CURSUS		= \033[s
J_CURSUS		= \033[u
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
	@echo "[1 / 1] - $(B_MAGENTA)$@$(NONE)"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)
	@echo "$(B_GREEN)Compilation done !$(NONE)"

all: $(NAME)

clean:
	@rm -Rf $(BUILD)
	@echo "$(B_RED)$(BUILD)$(NONE) -> $(B_GREEN)Delete$(NONE)"

fclean: clean
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE)  -> $(B_GREEN)Delete$(NONE)"

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@mkdir $@ $(DIRS);

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@