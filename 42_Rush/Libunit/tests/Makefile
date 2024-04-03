# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 15:19:17 by kaye              #+#    #+#              #
#    Updated: 2022/01/10 01:04:28 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
IFLAGS	= -I. -I../framework/inc
LFLAGS	= -L../framework -lunit
BFLAGS	= 0

# DIRECTORIES

BUILD 			:= .build
LUNIT_DIR		:= ../framework
SRC_DIR 		:= function_to_test \
				   strlen \
				   strcpy \
				   strcmp \
				   atoi \
				   infini
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SRC_DIR))

# OTHER MAKE

MAKEUNIT := $(LUNIT_DIR) all

# FILES

LUNIT			:= libunit.a
NAME			:= tests
SRC				:= main.c
SUB_SRC			:= atoi.c \
				   strcmp.c \
				   strcpy.c \
				   strlen.c \
				   infini.c
SRC				+= $(addprefix function_to_test/, $(SUB_SRC))
SUB_SRC			:= 00_strlen_launcher.c \
				   01_strlen_basic_test.c \
				   02_strlen_null_test.c
SRC				+= $(addprefix strlen/, $(SUB_SRC))
SUB_SRC			:= 00_strcpy_launcher.c \
				   01_strcpy_basic_test.c \
				   02_strcpy_bus_test.c \
				   03_strcpy_abrt_test.c
SRC				+= $(addprefix strcpy/, $(SUB_SRC))
SUB_SRC			:= 00_strcmp_launcher.c \
				   01_strcmp_basic_test.c \
				   02_strcmp_null_test.c
SRC				+= $(addprefix strcmp/, $(SUB_SRC))
SUB_SRC			:= 00_atoi_launcher.c \
				   01_atoi_basic_test.c \
				   02_atoi_intmax_test.c \
				   03_atoi_intmin_test.c \
				   04_atoi_intmax_overflow_test.c \
				   05_atoi_intmin_overflow_test.c \
				   06_atoi_divise_by_zero_test.c
SRC				+= $(addprefix atoi/, $(SUB_SRC))
SUB_SRC			:= 00_infini_launcher.c \
				   01_infini_loop_test.c
SRC				+= $(addprefix infini/, $(SUB_SRC))
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
	-./tests 2>/dev/null

bonus: MAKEUNIT := $(LUNIT_DIR) bonus
bonus: BFLAGS = 1
bonus: $(NAME)

$(NAME): $(OBJ) $(LUNIT_DIR)/$(LUNIT)
	@printf "$(CL_LINE)"
	@echo "$(B_BLUE)>>> Tests$(NONE)"
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)
	@echo "[1 / 1] - $(B_MAGENTA)$@$(NONE)"

clean:
	@$(MAKE) -C $(LUNIT_DIR) clean 1>/dev/null
	@rm -Rf $(BUILD)
	@echo "$(B_RED)OBJ$(NONE) : $(B_GREEN)Delete$(NONE)"

fclean: clean
	@$(MAKE) -C $(LUNIT_DIR) fclean
	@rm -Rf $(NAME)
	@echo "$(B_RED)$(NAME)$(NONE) : $(B_GREEN)Delete$(NONE)"

re: fclean all

.PHONY: all test clean fclean re

$(BUILD):
	@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:%.c | $(BUILD)
	@printf "$(CL_LINE)Compiling srcs object : $(B_CYAN)$< $(NONE)...\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -D BONUS=$(BFLAGS)

$(LUNIT_DIR)/$(LUNIT):
	@printf "$(CL_LINE)"
	@echo "$(B_BLUE)>>> Libunit$(NONE)"
	@$(MAKE) -C $(MAKEUNIT)