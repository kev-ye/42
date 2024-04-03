# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 15:14:42 by kaye              #+#    #+#              #
#    Updated: 2021/11/28 22:06:32 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
IFLAGS	= -I./incs -I./libft/inc -I./mlx/
LFLAGS	= -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit -lm
BFLAGS	= 0

# DIRECTORIES

BUILD 			:= .build
SRC_DIR 		:= srcs
SUB_DIR 		:= engine \
				   mlx \
				   parser \
				   utils
OBJ_DIR 		:= $(BUILD)/obj
LIBFT_DIR		:= ./libft
MLX_DIR			:= ./mlx
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME			:= cub3D
MLX				:= libmlx.dylib
SRC				:= main.c
SUB_SRC			:= configParsing.c \
				   infoParsing.c \
				   infoConfigParsing.c \
				   mapConfigParsing.c \
				   mapParsing.c \
				   mapParsing2.c
SRC				+= $(addprefix parser/, $(SUB_SRC))
SUB_SRC			:= startGame.c \
				   playerInitialize.c \
				   texInitialize.c \
				   keyControl.c \
				   playerMove.c \
				   playerRotation.c \
				   drawTools.c \
				   drawing.c \
				   rayCastingUtils.c \
				   rayCasting.c
SRC				+= $(addprefix engine/, $(SUB_SRC))
SUB_SRC			:= utils.c \
				   tools.c \
				   clean.c \
				   mlxClean.c
SRC				+= $(addprefix utils/, $(SUB_SRC))
OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)

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

ifeq ($(shell uname), Linux)
$(NAME): IFLAGS 	= -I./incs -I./libft/inc -I./mlx_linux/
$(NAME): LFLAGS	= -L./libft -lft -L./mlx_linux -lmlx_Linux -lXext -lX11 -lm
$(NAME): MLX_DIR = ./mlx_linux
$(NAME): MLX = libmlx.a
endif

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(CL_LINE)"
	@echo "[1 / 4] - $(B_MAGENTA)CUB3DOBJ$(NONE)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "[2 / 4] - $(B_MAGENTA)Libft$(NONE)"
	@$(MAKE) -C $(MLX_DIR) >/dev/null
	@echo "[3 / 4] - $(B_MAGENTA)MLX$(NONE)"
	@cp $(MLX_DIR)/$(MLX) .
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)
	@echo "[4 / 4] - $(B_MAGENTA)$@$(NONE)"


bonus: BFLAGS = 1
bonus: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -Rf $(BUILD)
	@echo "$(B_RED)$(BUILD)$(NONE) : $(B_GREEN)Delete$(NONE)"

ifeq ($(shell uname), Linux)
fclean: MLX_DIR =./mlx_linux
fclean: MLX = libmlx.a
endif
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean >/dev/null
	@rm -Rf $(MLX)
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE) : $(B_GREEN)Delete$(NONE)"

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -D BONUS=$(BFLAGS)