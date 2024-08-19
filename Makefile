# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 19:22:40 by hluiz-ma          #+#    #+#              #
#    Updated: 2024/08/19 20:53:40 by hluiz-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project settings
NAME = so_long
CC = cc #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g
RM= rm -rf

# Paths
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

# Source files
SRCS = main.c map.c map2.c map_init.c gameover.c gamefrees.c render.c render2.c sprites.c player.c moves.c moves2.c map_checks.c map_checks2.c exit.c goblin.c goblin_moves.c goblin_init.c enemy.c enemy_moves.c enemy_init.c combat.c combat_utils.c \
utils.c utils2.c victory_and_lose.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)
BONUS = 

# Scripts
TEST = val.sh

# Default target
all: $(NAME)

# Linking the final executable
$(NAME):	$(SRCS) $(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)  
			@echo "\033[1;32m[ ✔ ] $(NAME) ready!\033[0m"
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
				
bonus:		$(OBJS) $(OBJS_BONUS)
			@$(NAME) $^
			@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled Libft with Bonus.\033[0m"

# Compiling object files
%.o: %.c 
			@$(CC) $(CFLAGS) -c $^ -o $@
			@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"

# Cleaning object files
clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object files deleted\033[0m"

# Full cleanup
fclean:		clean
			@$(RM) $(NAME) $(MLX_DIR)
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
			
			
.PHONY:		all clean fclean re
