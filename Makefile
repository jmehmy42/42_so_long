# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 14:25:19 by jmehmy            #+#    #+#              #
#    Updated: 2025/04/03 15:00:12 by jmehmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = src/main.c src/graphics.c src/parse_map.c src/read_map.c src/useful_for_mlx.c src/useful_functions.c
OBJS = ${SRCS:.c=.o}

LIBFT = includes/libft
MLX = includes/mlx_Linux
EXT_LIB = libmlx.a

CC = cc
RM = rm -fr
CFLAGS = -Wall -Wextra -Werror -g -O3 -Iinclude -I$(LIBFT) -I$(MLX)
LDFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -L/usr/include/X11/extensions -lX11 -lXext

all: ${EXT_LIB} libft.a ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -g $(OBJS) $(EXT_LIB) $(CFLAGS) $(LDFLAGS) -o $(NAME)

${EXT_LIB}:
	@if [ ! -f ${EXT_LIB} ]; then \
		make -C ${MLX}; \
		cp ${MLX}/${EXT_LIB} .; \
		cp ${MLX}/mlx.h includes/; \
	fi

libft.a:
	@if [ ! -f ${LIBFT}/libft.a ]; then \
		make -C ${LIBFT}; \
		make -C ${LIBFT} CFLAGS=" -g -Wall -Wextra -Werror -fPIC"; \
	fi

clean:
	${RM} ${OBJS} a.out

fclean: clean
	${RM} ${NAME} ${EXT_LIB}
	make -C ${LIBFT} fclean
	make -C ${MLX} clean

re: fclean all