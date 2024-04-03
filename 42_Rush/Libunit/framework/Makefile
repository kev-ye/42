# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 23:01:02 by kaye              #+#    #+#              #
#    Updated: 2022/01/09 17:55:49 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
IFLAGS	= -I./inc
BFLAGS	= 0

# DIRECTORIES

BUILD 			:= .build
SRC_DIR 		:= src
SUB_DIR 		:= utils
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME			:= libunit.a
SRC				:= list.c \
				   print.c \
				   run_test.c
SUB_SRC			:= unit_bzero.c \
				   unit_calloc.c \
				   unit_strlen.c \
				   unit_putstr_fd.c \
				   unit_putendl_fd.c \
				   unit_putnbr_fd.c \
				   unit_singleton.c \
				   unit_clean.c
SRC				+= $(addprefix utils/, $(SUB_SRC))
OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# ANSCII CODE

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

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@echo "[1 / 2] - $(B_MAGENTA)LIBUNITOBJ$(NONE)"
	@ar -rcs $@ $^
	@echo "[2 / 2] - $(B_MAGENTA)$@$(NONE)"

bonus: BFLAGS = 1
bonus: $(NAME)

clean:
	@rm -Rf $(BUILD)

fclean: clean
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE) : $(B_GREEN)Delete$(NONE)"

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -D BONUS=$(BFLAGS)