# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfradet <nfradet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/18 02:16:14 by asangerm          #+#    #+#              #
#    Updated: 2024/08/28 16:37:14 by nfradet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME		=	cub3D

BONUS_NAME	=	cub3D_bonus

# Flags
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
LM			=	-lm
MFLAGS		=	-lX11 -lXext
INC			=	-I./includes

# Directories
VPATH   	=   src/ src/shared_parsing src/shared_movement \
				src/shared_display 	src/bonus src/mandatory

OBJ_DIR		=	obj/
LIB_DIR		=	libft/
MLX_DIR		=	minilibx-linux/

# .c and .o files	
SHARED_PARSING	=		shared_parsing.c	\
						parsing_utils.c		\
						map.c				\
						map_checker.c		\
						colors.c			\
						shared_textures.c	\
						shared_endinit.c
SHARED_DISPLAY	=		minimap.c			\
						draw_utils.c		\
						floor_ceil.c		\
						player_icon.c		\
						drawing.c			\
						shared_raycasting.c
SHARED_MOVEMENT	=		keyboard.c			\
						player.c

MANDATORY		=		ending.c			\
						init_mand.c			\
						move.c				\
						main.c				\
						parsing.c			\
						texture.c			\
						draw.c			\
						raycasting.c		
SRC				=		$(SHARED_PARSING)			\
						$(SHARED_MOVEMENT)			\
						$(SHARED_DISPLAY)			\
						$(MANDATORY)
OBJ				=		$(SRC:%.c=$(OBJ_DIR)%.o)

BONUS			=		door_handler.c		\
						main_bonus.c		\
						texture_bonus.c		\
						parsing_bonus.c		\
						ending_bonus.c		\
						move_bonus.c		\
						fps.c				\
						raycasting_bonus.c	\
						door.c				\
						draw_bonus.c
SRC_BONUS		=		$(SHARED_PARSING)			\
						$(SHARED_MOVEMENT)			\
						$(SHARED_DISPLAY)			\
						$(BONUS)
OBJ_BONUS		=		$(SRC_BONUS:%.c=$(OBJ_DIR)%.o)

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

bonus		:	ascii_art $(BONUS_NAME)

# ASCII Art at the beginning
ascii_art		:
	@echo $(ASCII_ART)

# The name rule
$(NAME)			:	$(OBJ_DIR) $(OBJ) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Compiling the whole project -> ⏳$(RESET)"
	@$(CC) $(OBJ) $(LIBFT) $(MLX) $(MFLAGS) -lm -o $@
	@echo "$(GREEN)Project successfuly compiled -> ✅$(RESET)\n"

$(BONUS_NAME)	:	$(OBJ_DIR) $(OBJ_BONUS) $(LIBFT) $(MLX)
	@echo "$(YELLOW)Compiling the whole project -> ⏳$(RESET)"
	@$(CC) $(OBJ_BONUS) $(LIBFT) $(MLX) $(MFLAGS) -lm -o $@
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
	@rm -rf $(BONUS_NAME)
	@make fclean -sC $(LIB_DIR)
	@echo "$(GREEN)Done -> ✅$(RESET)\n"
re				:	fclean all
