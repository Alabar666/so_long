# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 19:22:40 by hluiz-ma          #+#    #+#              #
#    Updated: 2024/07/04 21:11:29 by hluiz-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext
GNL = get_next_line.c get_next_line_utils.c
SRCS = so_long.c map.c gameover.c sprites.c player.c moves.c map_checks.c
BONUS = 
RM= rm -rf

all: $(NAME)

$(NAME):	$(SRCS) $(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) $(GNL) -o $(NAME)  
			@echo "\033[1;32m[ ✔ ] $(NAME) ready!\033[0m"
			@echo "\033[0;31m𓄿 𓅓  Made by Alabar 𓄿 𓅓"
			
$(LIBFT):
				@make --silent -C $(LIBFT_DIR)			
			
# Build minilibx-linux library
$(MLX): $(MLX_DIR)
	@rm -rf minilibx-linux/.git
	@make -C $^ > /dev/null 2>&1

$(MLX_DIR):
	@echo "\033[1;35m[ ✔ ] Preparing minilibx...\033[0m"
	@git clone https://github.com/42Paris/minilibx-linux.git > /dev/null 2>&1
				
bonus:		$(OBJS) $(OBJS_BONUS)
			@$(NAME) $^
			@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled Libft with Bonus.\033[0m"

%.o: %.c 
			@$(CC) $(CFLAGS) -c $^ -o $@
			@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"


clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object files deleted\033[0m"

fclean:		clean
			@$(RM) $(NAME) $(MLX_DIR)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Executable and Minilibx deleted.\033[0m"

re: 		fclean all
			
.PHONY:		all clean fclean re
