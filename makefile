# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asangerm <asangerm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 02:16:14 by asangerm          #+#    #+#              #
#    Updated: 2024/06/18 17:59:43 by asangerm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME	=	cube3d

# Flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
LM		=	-lm
MFLAGS	=	-lX11 -lXext
INC		=	-I./includes

# Directories
VPATH   =   src/ src/parsing src/keyboard src/ending src/init
OBJ_DIR	=	obj/
LIB_DIR	=	libft/
MLX_DIR	=	minilibx-linux/

# .c and .o files
PARSING		=	parsing0.c
INIT		=	init0.c
KEYBOARD	=	keyboard0.c
ENDING		=	ending0.c	
SRC			=	$(PARSING)	\
				$(INIT)		\
				$(KEYBOARD)	\
				$(ENDING)	\
				main.c
OBJ			=	$(SRC:%.c=$(OBJ_DIR)%.o)

# .a files
LIBFT	=	$(LIB_DIR)libft.a
MLX		=	$(MLX_DIR)libmlx.a

# Colors and styles
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
RESET	=	\033[0m

# ASCII art
ASCII_ART	=	"$(BLUE)   ___      _            _____   ___\n  / __\   _| |__   ___  |___ /  /   \ \n / / | | | | '_ \ / _ \   |_ \ / /\ /\n/ /__| |_| | |_) |  __/  ___) / /_//\n\____/\__,_|_.__/ \___| |____/___,'\n       by asangerm and nfradet$(RESET)\n"

# The main rule
all			:	ascii_art $(NAME)

# ASCII Art at the beginning
ascii_art		:
	@echo $(ASCII_ART)

# The name rule
$(NAME)			:	$(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Compiling the whole project -> ⏳$(RESET)"
	@$(CC) $(OBJ) $(LIBFT) $(MLX) $(MFLAGS) -o $@
	@echo "$(GREEN)Project successfuly compiled -> ✅$(RESET)\n"

# The libft rule
$(LIBFT)		:	$(LIB_DIR)
	@echo "$(YELLOW)Compiling my libft -> ⏳$(RESET)"
	@make all -sC $<
	@echo "$(GREEN)Libft successfuly compiled -> ✅$(RESET)\n"

# The mlx rule
$(MLX)			:	$(MLX_DIR)
	@echo "$(YELLOW)Compiling minilibx -> ⏳$(RESET)"
	@make all -sC $< > /dev/null 2>&1
	@echo "$(GREEN)Minilibx successfuly compiled -> ✅$(RESET)\n"

# Compile .c to .o files
$(OBJ_DIR)%.o	:	%.c 
	@echo "$(YELLOW)Compiling project src -> ⏳$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(GREEN)Src's project successfuly compiled -> ✅$(RESET)\n"

# Create the obj directory
$(OBJ_DIR)		:
	@mkdir -p $@

# Clean, fclean and re rules
clean			:
	@echo "$(RED)Cleaning obj files -> 🗑️$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -sC $(LIB_DIR)
	@make clean -sC $(MLX_DIR) > /dev/null 2>&1
	@echo "$(GREEN)Done -> ✅$(RESET)\n"

fclean			:	clean
	@echo "$(RED)Cleaning program -> 🗑️$(RESET)"
	@rm -rf $(NAME)
	@make fclean -sC $(LIB_DIR)
	@echo "$(GREEN)Done -> ✅$(RESET)\n"
re				:	fclean all