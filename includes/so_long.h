/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:20:16 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/08 18:46:36 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "fcntl.h"
# include "libft/libft.h"
# include "mlx_Linux/mlx.h"
# include "unistd.h"

# define ERROR -1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define IMG_SIZE 40

# define GHOST "./textures/ghost.xpm"
# define WALL "./textures/wall.xpm"
# define FLOOR "./textures/grass.xpm"
# define ITEMS "./textures/book.xpm"
# define CLOSED "./textures/exit_close.xpm"
# define OPENED "./textures/exit_open.xpm"

typedef struct s_pack
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	void	*player;
	void	*items;
	void	*exit_close;
	void	*exit_open;
}			t_pack;

typedef struct s_map
{
	char	*map;
	char	**split_map;
	char	**copy;
	int		items;
	int		exit;
	int		start;
	int		copy_items;
	int		copy_exit;
	int		player_x;
	int		player_y;
	int		x_exit;
	int		y_exit;
	int		height;
	int		player_exit;
	int		open_door;
	char	tile_under_player;
	t_pack	*m_pack;
}			t_map;

typedef struct s_rmap
{
	char	*buffer;
	char	*result;
	char	*tmp;
	int read_return ;
}			t_rmap;

void		get_positions(t_map *s_map);
int			char_finder(char *s, char c);
int			free_mem(char *s1, char *s2);
int			ft_error(char *message);
int			read_map(t_map *s_map, int fd);
int			verify_map(t_map *s_map);
void		graphics(t_map *s_map);
void		*set_image(t_map *map, char *path);
void		image_2_map(t_map *map, void *image, int x, int y);
void		handle_event(t_map *map, int new_x, int new_y, int *items_count);
void		del_and_free(t_map *map, int code);
void		close_window(t_map *map);
void		delete_textures(t_map *map);
void		load_textures(t_map *map);
void		free_mlx_window(t_map *map);
void		free_mlx(t_map *map);
void		item_collected(t_map *map, int *items_count);
void		movement(t_map *map, int x, int y);
int			key_hook(int keycode, t_map *map);
void		render_map(t_map *map, int x, int y);
void		draw_exit(t_map *map, int x, int y);
void		unlock_exit(t_map *map);

#endif