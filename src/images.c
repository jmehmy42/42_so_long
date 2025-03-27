/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:02:47 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 19:08:03 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void    draw_floor(t_window *mlx, int x, int y)
{
    void *img;
    char *path_name;
    int size;

    size = 50;
    path_name = "./textures/floor.xpm";
    img = mlx_xpm_file_to_image(mlx->mlx, path_name, &size, &size);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x, y);
}

void    draw_wall(t_window *mlx, int x, int y)
{
    void *img;
    char *path_name;
    int size;

    size = 50;
    path_name = "./textures/wall.xpm";
    img = mlx_xpm_file_to_image(mlx->mlx, path_name, &size, &size);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x, y);
}

void    draw_player(t_window *mlx, int x, int y)
{
    void *img;
    char *path_name;
    int size;

    size = 50;
    path_name = "./textures/player.xpm";
    img = mlx_xpm_file_to_image(mlx->mlx, path_name, &size, &size);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x, y);
}
void    draw_exit(t_window *mlx, int x, int y)
{
    void *img;
    char *path_name;
    int size;

    size = 50;
    path_name = "./textures/exit.xpm";
    img = mlx_xpm_file_to_image(mlx->mlx, path_name, &size, &size);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x, y);
}

void draw_collectible(t_window *mlx, int x, int y)
{
    void *img;
    char *path_name;
    int size;

    size = 50;
    path_name = "./textures/collectible.xpm";
    img = mlx_xpm_file_to_image(mlx->mlx, path_name, &size, &size);
    mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x, y);
}