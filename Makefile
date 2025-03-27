# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 11:59:54 by jmehmy            #+#    #+#              #
#    Updated: 2025/03/27 18:54:50 by jmehmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = src/main.c src/map.c src/player.c src/window.c src/keys.c src/images.c src/check_map.c
OBJS = ${SRCS:.c=.o}

LIBFT = include/libft
MLX = include/mlx_Linux
EXT_LIB = libmlx.a

CC = gcc
RM = rm -fr
CFLAGS = -Wall -Wextra -Werror -O3 -Iinclude -I$(LIBFT) -I$(MLX)
LDFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -L/usr/include/X11/extensions -lX11 -lXext

all: ${EXT_LIB} libft.a ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(EXT_LIB) -g $(CFLAGS) $(LDFLAGS) -o $(NAME)

${EXT_LIB}:
	make -C ${MLX}
	cp ${MLX}/${EXT_LIB} .
	cp ${MLX}/mlx.h include/

libft.a:
	make -C ${LIBFT}

clean:
	${RM} ${OBJS} a.out

fclean: clean
	${RM} ${NAME} ${EXT_LIB}
	make -C ${LIBFT} fclean
	make -C ${MLX} clean

re: fclean all
