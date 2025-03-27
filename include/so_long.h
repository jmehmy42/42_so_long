/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:47 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 19:09:27 by jmehmy           ###   ########.fr       */
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
# include "limits.h"

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
int error_check(int fd, t_list **map, int line_nbr, int *score);
int	check_rectangular (char *file, int total_lines);
int count_lines_in_file(char *file);
int handle_key_press(int key, t_window *mlx);
int exit_game(t_window *mlx);
int show_movecount_in_win(t_window *mlx);
void    create_map(t_window *mlx, t_list *map);
void draw_img_to_map (t_window *mlx, char *line, int line_count);
void    draw_background (t_window *mlx, char *line, int line_count);
int	check_wall(char *line);
int check_game_components(char *line, int *map_comps);
int error_check (int fd, t_list **map, int line_nbr, int *score);
void    move_player(t_window *mlx, int direction);
char *next_position (int dir, t_list *line, int counter);
t_list *find_player (int *counter, t_list *line);
int handle_key_press(int key, t_window *mlx);
void    move_player(t_window *mlx, int direction);
char *next_position (int dir, t_list *line, int counter);
t_list *find_player (int *counter, t_list *line);
void draw_collectible(t_window *mlx, int x, int y);
void    draw_exit(t_window *mlx, int x, int y);
void    draw_player(t_window *mlx, int x, int y);
void    draw_wall(t_window *mlx, int x, int y);
void    draw_floor(t_window *mlx, int x, int y);

#endif
