# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 13:39:40 by kaye              #+#    #+#              #
#    Updated: 2021/06/28 12:44:51 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror -g3 -fsanitize=address
IFLAGS 	= -I./libft/inc -I./incs

# DIRECTORIES

BUILD 			:= .build
INC_DIR			:= incs
SRC_DIR 		:= srcs
LFT_DIR			:= libft
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

SERVER			:= server
SERVER_B		:= server_bonus
CLIENT			:= client
CLIENT_B		:= client_bonus
SRC_COMMON		:= common.c \
				   utils.c
SRC_SERVER		:= server.c
SRC_CLIENT		:= client.c
SRC_SERVER_B	:= server_bonus.c
SRC_CLIENT_B	:= client_bonus.c
OBJ_COMMON		:= $(SRC_COMMON:%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER		:= $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER_B	:= $(SRC_SERVER_B:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT		:= $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT_B	:= $(SRC_CLIENT_B:%.c=$(OBJ_DIR)/%.o)

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

$(SERVER): $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON)
	@echo "Creating $(RED_COLOR) $(SERVER) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_SERVER) $(IFLAGS) $(OBJ_COMMON) -o $(SERVER)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(SERVER) $(BLUE_COLOR)done$(DEFAULT_COLOR)"
	@echo "Creating $(RED_COLOR) $(CLIENT) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_CLIENT) $(IFLAGS) $(OBJ_COMMON) -o $(CLIENT)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(CLIENT) $(BLUE_COLOR)done$(DEFAULT_COLOR)"

$(SERVER_B): $(OBJ_SERVER_B) $(OBJ_CLIENT_B) $(OBJ_COMMON)
	@echo "Creating $(RED_COLOR) $(SERVER_B) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_SERVER_B) $(IFLAGS) $(OBJ_COMMON) -o $(SERVER_B)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(SERVER_B) $(BLUE_COLOR)done$(DEFAULT_COLOR)"
	@echo "Creating $(RED_COLOR) $(CLIENT_B) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(OBJ_CLIENT_B) $(IFLAGS) $(OBJ_COMMON) -o $(CLIENT_B)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(CLIENT_B) $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(SERVER)

bonus: $(SERVER_B)

clean:
	rm -Rf $(BUILD)
fclean: clean
	rm -Rf $(SERVER)
	rm -Rf $(SERVER_B)
	rm -Rf $(CLIENT)
	rm -Rf $(CLIENT_B)

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS);

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@