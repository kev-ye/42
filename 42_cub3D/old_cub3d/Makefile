# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/16 18:53:03 by kaye              #+#    #+#              #
#    Updated: 2021/03/01 20:06:22 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION ##################################################################

CC 			= gcc
CFLAG 		= -Wall -Wextra -Werror
IFLAG 		= -I./inc -I./libft/inc -I./mlx/mlx
IFLAG_B 	= -I./inc_bonus -I./libft/inc -I./mlx/mlx
LFLAG 		= -L./mlx/mlx -lmlx -lm -framework OpenGL -framework AppKit
IFLAGS_L 	= -I./inc -I./libft/inc -I./mlx/mlx_linux
IFLAGS_L_B 	= -I./inc_bonus -I./libft/inc -I./mlx/mlx_linux
LFLAG_L 	= -L./mlx/mlx_linux -lmlx_Linux -lXext -lX11 -lm


# DIRECTORY ####################################################################

BUILD 		:= .build
BUILD_B 	:= .build_bonus
INC_DIR 	:= inc
INC_DIR_B	:= inc_bonus
SRC_DIR 	:= src
SRC_DIR_B	:= src_bonus
SUB_DIR 	:= engine \
		   	   events \
			   utils \
		   	   parser_map \
			   parser_map_file
LFT_DIR 	:= libft
MLX_DIR 	:= mlx/mlx
MLX_DIR_L 	:= mlx/mlx_linux
OBJ_DIR 	:= $(BUILD)/obj
OBJ_DIR_B 	:= $(BUILD_B)/obj_bonus
DIRS		:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))
DIRS_B		:= $(OBJ_DIR_B) $(addprefix $(OBJ_DIR_B)/, $(SUB_DIR))

# FILE #########################################################################

NAME  	:= cub3D
LIBFT 	:= libft.a
MLX   	:= libmlx.dylib
MLX_L   := libmlx_Linux.a
SRC	  	:= main.c
SUB_SRC := img.c \
		   mapping.c \
		   move.c \
		   rotation.c \
		   ray_casting_utils.c \
		   ray_casting.c \
		   set_camera.c \
		   set_sprites.c \
		   set_textures.c \
		   sprite_casting_utils.c \
		   sprite_casting.c
SRC 	+= $(addprefix engine/, $(SUB_SRC))
SUB_SRC := event_key.c \
		   events.c
SRC		+= $(addprefix events/, $(SUB_SRC))
SUB_SRC := check_map.c \
		   check_x.c \
		   check_y.c \
		   get_map.c \
		   get_map2.c \
		   get_player_place.c
SRC		+= $(addprefix parser_map/, $(SUB_SRC))
SUB_SRC := check_file_line_id.c \
		   check_file_line_map.c \
		   check_file_name.c \
		   check_file.c \
		   check_path.c \
		   floor_ceiling.c \
		   get_color.c \
		   get_path.c \
		   get_resolution.c \
		   init_desc.c
SRC		+= $(addprefix parser_map_file/, $(SUB_SRC))
SUB_SRC := color.c \
		   free.c \
		   msg_error.c \
		   quit.c \
		   bmp.c
SRC		+= $(addprefix utils/, $(SUB_SRC))
OBJ	  	:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# FILE - BONUS #################################################################

NAME_B		:= cub3D_bonus
SRC_B	  	:= main_bonus.c
SUB_SRC_B 	:= img_bonus.c \
		   	   mapping_bonus.c \
		   	   move_bonus.c \
		   	   rotation_bonus.c \
		   	   ray_casting_utils_bonus.c \
		   	   ray_casting_bonus.c \
		   	   set_camera_bonus.c \
		   	   set_sprites_bonus.c \
		   	   set_textures_bonus.c \
			   sprite_drawing_bonus.c \
		   	   sprite_casting_utils_bonus.c \
		   	   sprite_casting_bonus.c \
		   	   life_gun_bonus.c \
			   game_music_bonus.c \
		   	   hud_bonus.c \
			   mini_map_bonus.c
SRC_B 		+= $(addprefix engine/, $(SUB_SRC_B))
SUB_SRC_B 	:= event_key_bonus.c \
		       events_bonus.c
SRC_B		+= $(addprefix events/, $(SUB_SRC_B))
SUB_SRC_B 	:= check_map_bonus.c \
		   	   check_x_bonus.c \
		   	   check_y_bonus.c \
		   	   get_map_bonus.c \
			   get_map_2_bonus.c \
		   	   get_player_place_bonus.c
SRC_B		+= $(addprefix parser_map/, $(SUB_SRC_B))
SUB_SRC_B 	:= check_file_line_id_bonus.c \
				check_file_line_id_2_bonus.c \
		   	   check_file_line_map_bonus.c \
		   	   check_file_name_bonus.c \
		   	   check_file_bonus.c \
		   	   check_path_bonus.c \
		   	   floor_ceiling_bonus.c \
		   	   get_color_bonus.c \
		   	   get_path_bonus.c \
		   	   get_resolution_bonus.c \
		   	   init_desc_bonus.c
SRC_B		+= $(addprefix parser_map_file/, $(SUB_SRC_B))
SUB_SRC_B 	:= color_bonus.c \
		   	   free_bonus.c \
			   free_img_bonus.c \
		   	   msg_error_bonus.c \
		   	   quit_bonus.c \
		   	   bmp_bonus.c
SRC_B		+= $(addprefix utils/, $(SUB_SRC_B))
OBJ_B	  	:= $(SRC_B:%.c=$(OBJ_DIR_B)/%.o)

# COLORS #######################################################################

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m

# Makefile Macos / Linux #######################################################

ifeq ($(shell uname), Darwin)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@cp ./$(LFT_DIR)/$(LIBFT) .
	@cp ./$(MLX_DIR)/$(MLX) .
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAG) $(LFLAG) $(LIBFT) $(MLX) $^ -o $@
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

$(NAME_B): $(OBJ_B)
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@cp ./$(LFT_DIR)/$(LIBFT) .
	@cp ./$(MLX_DIR)/$(MLX) .
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAG_B) $(LFLAG) $(LIBFT) $(MLX) $^ -o $@
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

bonus: $(NAME_B)

clean:
	@$(MAKE) -C $(LFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -Rf $(BUILD)

clean_bonus:
	@$(MAKE) -C $(LFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -Rf $(BUILD_B)

fclean: clean
	@$(MAKE) -C $(LFT_DIR) fclean
	rm -Rf $(NAME) $(LIBFT) $(MLX)

fclean_bonus: clean_bonus
	@$(MAKE) -C $(LFT_DIR) fclean
	rm -Rf $(NAME_B) $(LIBFT) $(MLX)

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus
	
$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS)

$(BUILD_B):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS_B)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAG) -c $< -o $@

$(OBJ_DIR_B)/%.o:$(SRC_DIR_B)/%.c | $(BUILD_B)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAG_B) -c $< -o $@
	
endif

ifeq ($(shell uname), Linux)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(MLX_DIR_L)
	@cp ./$(LFT_DIR)/$(LIBFT) .
	@cp ./$(MLX_DIR_L)/$(MLX_L) .
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS_L) $^ -o $@ $(LFLAG_L) $(LIBFT) $(MLX_L)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

$(NAME_B): $(OBJ_B)
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(MLX_DIR_L)
	@cp ./$(LFT_DIR)/$(LIBFT) .
	@cp ./$(MLX_DIR_L)/$(MLX_L) .
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS_L_B) $^ -o $@ $(LFLAG_L) $(LIBFT) $(MLX_L)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

bonus: $(NAME_B)

clean:
	@$(MAKE) -C $(LFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR_L) clean
	rm -Rf $(BUILD)

clean_bonus:
	@$(MAKE) -C $(LFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR_L) clean
	rm -Rf $(BUILD_B)

fclean: clean
	@$(MAKE) -C $(LFT_DIR) fclean
	rm -Rf $(NAME) $(LIBFT) $(MLX_L)

fclean_bonus: clean_bonus
	@$(MAKE) -C $(LFT_DIR) fclean
	rm -Rf $(NAME_B) $(LIBFT) $(MLX_L)

re: fclean all

re_bonus: fclean_bonus bonus

.PHONY: all clean fclean re bonus clean_bonus fclean_bonus re_bonus
	
$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS)

$(BUILD_B):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS_B)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS_L) -c $< -o $@

$(OBJ_DIR_B)/%.o:$(SRC_DIR_B)/%.c | $(BUILD_B)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS_L_B) -c $< -o $@

endif