/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:47 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/26 19:03:54 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx_Linux/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"

# ifdef __linux__
#  define UP 119
#  define DOWN 115
#  define RIGHT 97
#  define LEFT 100
#  define ESC 65307
#endif

typedef struct s_data
{
	void	*img;
}				t_data;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_list	*map;
	int	score;
	int	count_move;
} t_window;

int	count_lines_in_file(char *file);
int error_check(int fd);
#endif
