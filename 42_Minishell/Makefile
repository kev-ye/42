# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 17:51:28 by kaye              #+#    #+#              #
#    Updated: 2021/06/26 23:20:10 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC			= clang
CFLAGS 		= -Wall -Wextra -Werror # -g3 -fsanitize=address
IFLAGS 		= -I./incs -I./libft/incs
LIBFLAGS 	= -L./libft -lft -lncurses -lreadline

# DIRECTORIES

BUILD		:= .build
LIB_DIR		:= libft
INC_DIR		:= incs
SRC_DIR		:= srcs
SUB_DIR		:= builtin \
			   execution \
			   general \
			   parser \
			   termcaps \
			   util
OBJ_DIR 	:= $(BUILD)/obj
DIRS		:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME	:= minishell
SRC		:= main.c
SUB_SRC	:= cd.c \
		   cd_utils.c \
		   clear.c \
		   echo.c \
		   env.c \
		   exit.c \
		   export.c \
		   pwd.c \
		   unset.c \
		   export_utils.c
SRC		+= $(addprefix builtin/, $(SUB_SRC))
SUB_SRC	:= exec_cmds.c \
		   search_executable.c \
		   multi_cmds_check.c \
		   cmds_syntax_check.c \
		   builtin_exec.c \
		   sys_exec.c \
		   flag_check.c \
		   create_fd_output.c \
		   create_fd_input.c \
		   create_fd_utils.c \
		   redir_parser_utils.c \
		   exec_all_in_one.c \
		   exec_all_in_one_utils.c \
		   exec_all_in_one_utils2.c \
		   first_cmd.c \
		   inter_cmd.c \
		   last_cmd.c \
		   lrv_utils.c \
		   lrv_utils2.c \
		   builtin_cmd_with_redir.c \
		   builtin_cmd_with_redir_utils.c
SRC		+= $(addprefix execution/, $(SUB_SRC))
SUB_SRC	:= args_parsing.c \
		   init_minishell.c \
		   prompt.c \
		   signals_handling.c \
		   singleton.c
SRC		+= $(addprefix general/, $(SUB_SRC))
SUB_SRC	:= parser_steps_1.c \
		   parser_steps_2.c \
		   parser.c \
		   quotes_handling.c
SRC		+= $(addprefix parser/, $(SUB_SRC))
SUB_SRC	:= history.c
SRC		+= $(addprefix termcaps/, $(SUB_SRC))
SUB_SRC	:= list_utils.c \
		   memory_management.c \
		   utils.c
SRC		+= $(addprefix util/, $(SUB_SRC))

OBJ 	:= $(SRC:%.c=$(OBJ_DIR)/%.o)

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
	@echo "Compiling $(RED_COLOR)Libft $(DEFAULT_COLOR)..."
	@$(MAKE) -C $(LIB_DIR) >/dev/null
	@echo "Creating $(RED_COLOR) $@ $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAGS) $(IFLAGS) $^ -o $@ $(LIBFLAGS)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

clean:
	@echo "Deleting $(CYAN_COLOR).o file $(DEFAULT_COLOR)of libft ..."
	@$(MAKE) clean -C $(LIB_DIR) >/dev/null
	@echo "Deleting $(CYAN_COLOR).o file $(DEFAULT_COLOR)of minishell ..."
	@rm -rf $(BUILD)

fclean: clean
	@echo "Deleting $(CYAN_COLOR)libft $(DEFAULT_COLOR)file ..."
	@$(MAKE) fclean -C $(LIB_DIR) >/dev/null
	@echo "Deleting $(CYAN_COLOR)minishell $(DEFAULT_COLOR)file ..."
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@rm -f .minishell_history

re: fclean all

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS)
	
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c ./incs/minishell.h | $(BUILD)
	@echo "Compiling $(YELLOW_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean
