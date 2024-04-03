# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 15:19:17 by kaye              #+#    #+#              #
#    Updated: 2022/01/10 01:07:36 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
IFLAGS	= -I. -I./libft/inc -I../framework/inc
LFLAGS	= -L./libft -lft -L../framework -lunit
BFLAGS	= 0

# DIRECTORIES

BUILD 			:= .build
LFT_DIR			:= ./libft
LUNIT_DIR		:= ../framework
SRC_DIR 		:= atoi \
				   strlen \
				   strchr \
				   strcmp \
				   strcpy \
				   strjoin \
				   strtrim \
				   toupper
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SRC_DIR))

# OTHER MAKE

MAKELFT := $(LFT_DIR) all
MAKEUNIT := $(LUNIT_DIR) all

# FILES

LFT				:= libft.a
LUNIT			:= libunit.a
NAME			:= real_tests
SRC				:= main.c
SUB_SRC			:= 00_atoi_launcher.c \
				   01_atoi_basic_test.c \
				   02_atoi_intmax_test.c \
				   03_atoi_intmin_test.c
SRC				+= $(addprefix atoi/, $(SUB_SRC))
SUB_SRC			:= 00_strlen_launcher.c \
				   01_strlen_basic_test.c
SRC				+= $(addprefix strlen/, $(SUB_SRC))
SUB_SRC			:= 00_strchr_launcher.c \
				   01_strchr_basic_test.c
SRC				+= $(addprefix strchr/, $(SUB_SRC))
SUB_SRC			:= 00_strcmp_launcher.c \
				   01_strcmp_basic_test.c 
SRC				+= $(addprefix strcmp/, $(SUB_SRC))
SUB_SRC			:= 00_strcpy_launcher.c \
				   01_strcpy_basic_test.c
SRC				+= $(addprefix strcpy/, $(SUB_SRC))
SUB_SRC			:= 00_strjoin_launcher.c \
				   01_strjoin_basic_test.c \
				   02_strjoin_null_string_test.c \
				   03_strjoin_empty_string_test.c
SRC				+= $(addprefix strjoin/, $(SUB_SRC))
SUB_SRC			:= 00_toupper_launcher.c \
				   01_toupper_basic_test.c \
				   02_toupper_invalid_char_test.c
SRC				+= $(addprefix toupper/, $(SUB_SRC))
SUB_SRC			:= 00_strtrim_launcher.c \
				   01_strtrim_basic_test.c \
				   02_strtrim_set_in_str_test.c \
				   03_strtrim_null_string_test.c
SRC				+= $(addprefix strtrim/, $(SUB_SRC))
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

test: $(NAME)
	./real_tests

bonus: MAKEUNIT := $(LUNIT_DIR) bonus
bonus: BFLAGS = 1
bonus: $(NAME)

$(NAME): $(OBJ) $(LFT_DIR)/$(LFT) $(LUNIT_DIR)/$(LUNIT)
	@printf "$(CL_LINE)"
	@echo "$(B_BLUE)>>> Tests$(NONE)"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)
	@echo "[1 / 1] - $(B_MAGENTA)$@$(NONE)"

clean:
	@$(MAKE) -C $(LFT_DIR) clean 1>/dev/null
	@$(MAKE) -C $(LUNIT_DIR) clean 1>/dev/null
	@rm -Rf $(BUILD)
	@echo "$(B_RED)OBJ$(NONE) : $(B_GREEN)Delete$(NONE)"

fclean: clean
	@$(MAKE) -C $(LFT_DIR) fclean
	@$(MAKE) -C $(LUNIT_DIR) fclean
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE) : $(B_GREEN)Delete$(NONE)"

re: fclean test

.PHONY: test clean fclean re

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -D BONUS=$(BFLAGS)

$(LFT_DIR)/$(LFT):
	@printf "$(CL_LINE)"
	@echo "$(B_BLUE)>>> Libft$(NONE)"
	@$(MAKE) -C $(MAKELFT)

$(LUNIT_DIR)/$(LUNIT):
	@printf "$(CL_LINE)"
	@echo "$(B_BLUE)>>> Libunit$(NONE)"
	@$(MAKE) -C $(MAKEUNIT)