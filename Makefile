# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 19:22:40 by hluiz-ma          #+#    #+#              #
#    Updated: 2024/08/24 17:00:00 by hluiz-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project settings
NAME = so_long
B_NAME = bonus_so_long
CC = cc #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I./include -I./minilibx-linux
RM = rm -rf

# Paths
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_DIR = ./src
SRCS_BONUS = ./bonus
MLX_DIR = ./minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
MLXFLAGS = -L $(MLX_DIR) -lmlx -lm -lX11 -lXext

# Source files
SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/map.c $(SRCS_DIR)/map2.c $(SRCS_DIR)/map_init.c \
$(SRCS_DIR)/gameover.c $(SRCS_DIR)/gamefrees.c $(SRCS_DIR)/render.c $(SRCS_DIR)/render2.c \
$(SRCS_DIR)/sprites.c $(SRCS_DIR)/player.c $(SRCS_DIR)/moves.c $(SRCS_DIR)/moves2.c \
$(SRCS_DIR)/map_checks.c $(SRCS_DIR)/map_checks2.c $(SRCS_DIR)/exit.c $(SRCS_DIR)/goblin.c \
$(SRCS_DIR)/goblin_moves.c $(SRCS_DIR)/goblin_init.c $(SRCS_DIR)/enemy.c \
$(SRCS_DIR)/enemy_moves.c $(SRCS_DIR)/enemy_init.c $(SRCS_DIR)/combat.c \
$(SRCS_DIR)/combat_utils.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/utils2.c \
$(SRCS_DIR)/victory_and_lose.c

BONUS = $(SRCS_BONUS)/main_bonus.c $(SRCS_BONUS)/map.c $(SRCS_BONUS)/map2.c $(SRCS_BONUS)/map_init.c \
$(SRCS_BONUS)/gameover.c $(SRCS_BONUS)/gamefrees.c $(SRCS_BONUS)/render.c $(SRCS_BONUS)/render2.c \
$(SRCS_BONUS)/sprites.c $(SRCS_BONUS)/player.c $(SRCS_BONUS)/moves.c $(SRCS_BONUS)/moves2.c \
$(SRCS_BONUS)/map_checks.c $(SRCS_BONUS)/map_checks2.c $(SRCS_BONUS)/exit.c $(SRCS_BONUS)/goblin.c \
$(SRCS_BONUS)/goblin_moves.c $(SRCS_BONUS)/goblin_init.c $(SRCS_BONUS)/enemy.c \
$(SRCS_BONUS)/enemy_moves.c $(SRCS_BONUS)/enemy_init.c $(SRCS_BONUS)/combat.c \
$(SRCS_BONUS)/combat_utils.c $(SRCS_BONUS)/utils.c $(SRCS_BONUS)/utils2.c \
$(SRCS_BONUS)/victory_and_lose.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

# Scripts
TEST = val.sh

# Default target
all: $(MLX) $(NAME)

# Linking the final executable
$(NAME):	$(SRCS) $(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)  
			@echo "\033[1;32m[ ✔ ] $(NAME) ready!\033[0m"
			@echo "\033[0;31m𓄿 𓅓  Made by Alabar 𓄿 𓅓"

# Building the bonus executable
bonus: $(B_NAME)

$(B_NAME): $(OBJS_BONUS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLXFLAGS) -o $(B_NAME)
			@echo "\033[1;32m[ ✔ ] $(B_NAME) ready!\033[0m"
			@echo "\033[0;31m𓄿 𓅓  Made by Alabar 𓄿 𓅓"
						
# Building the libft library			
$(LIBFT):
			@make --silent -C $(LIBFT_DIR)			
			
# Building the MLX library
$(MLX): $(MLX_DIR)
	@rm -rf minilibx-linux/.git
	@make -C $^ > /dev/null 2>&1

$(MLX_DIR):
	@echo "\033[1;35m[ ✔ ] Preparing minilibx...\033[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1
				

# Compiling object files
%.o: %.c 
			@$(CC) $(CFLAGS) -c $^ -o $@
			@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

# Cleaning object files
clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)
			@$(RM) $(SRCS_DIR)/*.o
			@$(RM) $(SRCS_BONUS)/*.o
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object files deleted\033[0m"

# Full cleanup
fclean:		clean
			@$(RM) $(NAME) $(B_NAME) $(MLX_DIR)
			@make fclean -C $(LIBFT_DIR)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Executable and Minilibx deleted.\033[0m"

# Rebuild everything
re: 		fclean all

# Leak testing
leak: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/invalid_map/empty_line_in_between.ber

# Run tests
test: re
	./$(TEST)			
						
.PHONY:		all clean fclean re bonus
