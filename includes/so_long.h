/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:20:16 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/01 17:29:50 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx_Linux/mlx.h"
# include "fcntl.h"
# include "stdio.h"
# include "unistd.h"

# define ERROR -1

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#define IMG_SIZE 40

# define GHOST "./textures/ghost.xpm"
# define WALL "./textures/wall.xpm"
# define FLOOR "./textures/grass.xpm"
# define ITEMS "./textures/book.xpm"
# define CLOSED "./textures/exit_close.xpm"
# define OPENED "./textures/exit_open.xpm"

typedef struct s_pack
{
    void *mlx;
    void *win;
    void *wall;
    void *floor;
    void *player;
    void *items;
    void *exit_close;
    void *exit_open;
} t_pack;

typedef struct s_map
{
    char *map;
    char **split_map;
    char **copy;
    int items;
    int exit;
    int start;
    int copy_items;
    int copy_exit;
    int player_x;
    int player_y;
    int height;
    t_pack *m_pack;
} t_map;

typedef struct s_rmap
{
    char *str;
    char *map;
    char *copy;
    int read_return;
} t_rmap;

void get_positions(t_map *s_map);
int char_finder(char *s, char c);
int free_mem(char *s1, char *s2);
int ft_error(char *message);
char *read_map(int fd);
int verify_map(t_map *s_map);
void graphics(t_map *map);
void *set_image (t_map *map, char *path);
void image_2_map(t_map *map, void *image, int x, int y);
void exit_free(t_map *map, char *message);
void clean_exit(t_map *map);

#endif