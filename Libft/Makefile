# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 20:41:06 by hluiz-ma          #+#    #+#              #
#    Updated: 2024/05/05 15:17:52 by hluiz-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
CC= cc
CFLAGS= -Wall -Wextra -Werror -c
OBJS= $(SRCS:.c=.o)
OBJS_BONUS= $(BONUS:.c=.o)
SRCS= ft_atoi.c ft_isalnum.c ft_putnbr_fd.c ft_strchr.c ft_strdup.c \
ft_strlen.c ft_tolower.c ft_toupper.c ft_isalpha.c ft_isdigit.c \
ft_putchar_fd.c ft_memcpy.c ft_isascii.c ft_isprint.c ft_putendl_fd.c \
ft_putstr_fd.c ft_strncmp.c ft_strrchr.c ft_memset.c ft_strlcat.c \
ft_strjoin.c ft_strlcpy.c ft_calloc.c ft_bzero.c ft_memchr.c ft_memcmp.c \
ft_memmove.c ft_strnstr.c ft_substr.c ft_striteri.c ft_strmapi.c \
ft_strtrim.c ft_itoa.c ft_split.c get_next_line.c get_next_line_utils.c ft_format.c \
ft_printf.c ft_putchar.c ft_putstr.c

RM= rm -rf  

BONUS= ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c \
ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c \
ft_lstiter_bonus.c


all: $(NAME)

$(NAME):	$(OBJS)
			@ar rcs $(NAME) $(OBJS)
			@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled Libft.\033[0m"
			@echo "\033[0;31m𓄿 𓅓  Made by Alabar 𓄿 𓅓"

bonus:		$(OBJS) $(OBJS_BONUS)
			@ar rcs $(NAME) $^
			@echo "\033[90m[\033[32mSuccess\033[90m]\033[32m Successfully compiled Libft with Bonus.\033[0m"


%.o: %.c #SHOW COMPILING
#$(SRCS):
			@$(CC) $(CFLAGS) -c $^ -o $@
			@echo "\033[90m[\033[32mOK\033[90m]\033[34m Compiling $<\033[0m"


clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Object files deleted\033[0m"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[90m[\033[91mDeleting\033[90m]\033[31m Libft.a deleted.\033[0m"

re: 		fclean all

help:
			@echo ----------------Comand List--------------------
			@echo make - To compile the Libft.
			@echo bonus - To compile the Bonus Libft.
			@echo clean - To remove objects.
			@echo fclean - To remove objects and Libft.
			@echo re - To remove objects and Libft and recompile.
			@echo -----------------------------------------------
			@echo "\n\e[0;36m@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@*++*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@*++*@@@@@@@@@@@@%*+++++**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@*++*@@@@@@@@@@@%+==+***===*@@@@@@@@%*+===+*@@@@@@@%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@*++*@@@@@@@@@@@*==*@@@@*+=+@@@@@@@%+==+*++=+*@@@@%=+=+++++++*@@@@@@@@@@@@@@@@@@@@@@\n@@@@@@@*++*@@@@@@@@@@@++=*@@@@@*==*@@@@@@*==*@@@%+=+*@@@@%%**==+***+@@@@@@@@@*+===++*@@@@@\n@@@@@@@*++*@@@@@@@@@@%+=+@@@@@@%+=*@@@@@@*+=*@@@@@%%%@@@@@@@@+=+@@@@@@@@@@@@*+==***==+%@@@\n@@@@@@@*++*@@@@@@@@@@*+=+@@@@@@%+=+@@@@@@@*==+**@@@@@@@@@@@@@+=+@@@@@@@@@@@@*==*@@@*==*@@@\n@@@@@@@*++*@@@@@@@@@@*+=*@@@@@@%+=+@@@@@@@@%*+==+*@@@@@@@@@@@+=+@@@@@@@@@@@@%**%@@@*==*@@@\n@@@@@@@*++*@@@@@@@@@@*+=+@@@@@@%+=+@@@@@@@@@@@**=++*@@@@@@@@@+=+@@@@@@@@@@@@@@@@@@*===%@@@\n@@@@@@@*++*@@@@@@@@@@@+=+@@@@@@*++*@@@@@@@@@@@@@%+==*@@@@@@@@+=+@@@@@@@@@@@@@@@@@*+==*@@@@\n@@@@@@@*++*@@@@@@@@@@@+==*@@@@@++=%@@@@@%**%@@@@@%+++@@@@@@@@+=+@@@@@@@@@@@@@@@%+=++%@@@@@\n@@@@@@@*++++++++++*@@@%+=+*@@%++++@@@@@@%+=+@@@@@@++=@@@@@@@@+=+@@@@@@@@@@@@@@@+==*@@@@@@@\n@@@@@@@%%%%********@@@@%++=++==+*%@@@@@@@*=++**%*+=++@@@@@@@@+=+@@@@@@@@@@@@@@*==*@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@%***%@@@@@@@@@@@%*++==+++*@@@@@@@@@+++@@@@@@@@@@@@@@%*%@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%***%@@@@@@@@@@@+++@@@@@@@@@@@@@@*==*@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*++*@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

			
.PHONY:		all clean fclean re
