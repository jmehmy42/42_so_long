# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 11:59:54 by jmehmy            #+#    #+#              #
#    Updated: 2025/03/25 12:41:44 by jmehmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= so_long

SRC	= ./src/check_map.c ./src/gnl.c ./src/gnl_helper.c ./src/main.c ./src/map.c ./src/handle_even.c ./src/init.c ./src/return.c ./src/utils.c \

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAG	= -Wall -Wextra	-Werror -g

all	: 	$(NAME)

%.o	:	%.c
		$(CC) $(CFLAG) -I/usr/includes -Imlx_Linux -O3 -c $< -o $@

$(NAME)	:	$(OBJ)
		make -C ./includes/mlx_Linux
		$(CC) $(OBJ) -L./includes/mlx_Linux -lmlx -L/usr/lib -Imlx_Linux -lXext -lX11 -lm -lz -o $(NAME)


clean	: 
		make -C ./includes/mlx_Linux clean
		rm -rf $(OBJ)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all

.PHONY	: all clean fclean re
