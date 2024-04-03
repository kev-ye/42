# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 11:34:23 by kaye              #+#    #+#              #
#    Updated: 2023/03/27 17:30:13 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

# COMPILATION

CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
IFLAGS 		= -I./inc
DBFLAG		= 0

# DIRECTORIES

BUILD 		:= .build
INC_DIR	 	:= inc
SRC_DIR  	:= src
OBJ_DIR 	:= $(BUILD)/obj
DIRS		:= $(OBJ_DIR)

# FILES

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME 		:= libft_malloc_$(HOSTTYPE).so
S_LINK		:= libft_malloc.so
TEST		:= test
SRC			:= malloc.c \
			   calloc.c \
			   realloc.c \
			   free.c \
			   show_alloc_mem.c \
			   show_alloc_mem_info.c \
			   show_alloc_mem_leak.c \
			   common.c \
			   utils.c
OBJ			:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# MAKEFILE

$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@echo "[1 / 2] - $(B_MAGENTA)MALLOC - OBJ$(NONE)"
	@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJ)
	@rm -rf $(S_LINK)
	@ln -s $(NAME) $(S_LINK) 2>/dev/null
	@echo "[2 / 2] - $(B_MAGENTA)$@$(NONE)"

all: $(NAME)

bonus: $(NAME)

debug: DBFLAG = 1
debug: $(NAME)

test: main.c $(NAME)
	@$(CC) $(CFLAGS) $(IFLAGS) main.c $(S_LINK) -o $(TEST)

clean:
	@rm -Rf $(BUILD)

fclean: clean
	@rm -Rf  $(NAME) $(S_LINK)
	@rm -f $(TEST)

re: fclean all

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_MAGENTA)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -fPIC -c $< -o $@ -D DEBUG=$(DBFLAG)

.PHONY: all clean fclean re