# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 16:59:07 by kaye              #+#    #+#              #
#    Updated: 2021/03/28 19:42:34 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror
IFLAGS 	= -I./inc

# DIRECTORIES

BUILD		:= .build
INC_DIR		:= inc
SRC_DIR		:= src
OBJ_DIR		:= $(BUILD)/obj
SUB_DIR		:= ctype \
			   memory \
			   string \
			   io \
			   list \
			   utile
PTF_DIR		:= $(SRC_DIR)/io/ft_printf
DIRS		:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME 	:= libft.a
PTF		:= libftprintf.a
SUB_SRC := ft_isalpha.c \
		   ft_isdigit.c \
		   ft_isalnum.c \
		   ft_isascii.c \
		   ft_isprint.c \
		   ft_toupper.c \
		   ft_tolower.c \
		   ft_isspace.c
SRC 	:= $(addprefix ctype/, $(SUB_SRC))
SUB_SRC := ft_memset.c \
		   ft_bzero.c \
		   ft_memcpy.c \
		   ft_memccpy.c \
		   ft_memmove.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_calloc.c
SRC 	+= $(addprefix memory/, $(SUB_SRC))
SUB_SRC := ft_strlen.c \
		   ft_strchr.c \
		   ft_strrchr.c \
		   ft_strncmp.c \
		   ft_strlcpy.c \
		   ft_strlcat.c \
		   ft_strnstr.c \
		   ft_atoi.c \
	 	   ft_strdup.c \
		   ft_substr.c \
		   ft_strjoin.c \
		   ft_strtrim.c \
		   ft_split.c \
		   ft_itoa.c \
		   ft_strmapi.c \
		   ft_itoa_base.c \
		   ft_strcpy.c \
		   ft_strcmp.c \
		   ft_strnlen.c \
		   ft_charinstr.c \
		   ft_strcat.c \
		   ft_atoll.c
SRC 	+= $(addprefix string/, $(SUB_SRC))
SUB_SRC	:= ft_putchar_fd.c \
		   ft_putstr_fd.c \
		   ft_putendl_fd.c \
		   ft_putnbr_fd.c \
		   ft_putchar.c \
		   ft_putstr.c \
		   get_next_line.c \
		   ft_printf.c
SRC		+= $(addprefix io/, $(SUB_SRC))
SUB_SRC	:= ft_lstnew.c \
		   ft_lstadd_front.c \
		   ft_lstsize.c \
		   ft_lstlast.c \
		   ft_lstadd_back.c \
		   ft_lstdelone.c \
		   ft_lstclear.c \
		   ft_lstiter.c \
		   ft_lstmap.c
SRC		+= $(addprefix list/, $(SUB_SRC))
SUB_SRC := ft_intlen_base.c \
		   get_next_line_utils.c
SRC		+= $(addprefix utile/, $(SUB_SRC))
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
	@echo "Creating $(RED_COLOR) $(FT_PRINTF) $(DEFAULT_COLOR)..."
	@$(MAKE) -C $(PTF_DIR)
	@cp $(PTF_DIR)/$(PTF) $(NAME)
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@ar -rcs $@ $^
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$@ $(BLUE_COLOR)done$(DEFAULT_COLOR)"
	
all: $(NAME)

clean:
		$(MAKE) -C $(PTF_DIR) clean
		rm -Rf $(BUILD)

fclean: clean
		$(MAKE) -C $(PTF_DIR) fclean
		rm -Rf $(NAME)

re: fclean all

$(BUILD):
		@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
		@mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD)
		@echo "Compiling $(YELLOW_COLOR)$< $(DEFAULT_COLOR)..."
		@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re