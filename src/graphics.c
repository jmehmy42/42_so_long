/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:49:30 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/01 17:28:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	item_collected(t_map *map, int *items_count)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	*items_count += 1;
	if (*items_count == map->items)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->exit_close);
	mlx_destroy_image(map->m_pack->mlx, map->m_pack->items);
	map->m_pack->items = set_image(map, ITEMS);
	map->split_map[map->player_y][map->player_x] = '0';
	while (map->split_map[y])
	{
		while (map->split_map[y][x])
		{
			if (map->split_map[y][x] == 'C')
				image_2_map(map, map->m_pack->items, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	movement(t_map *map, int x_move, int y_move)
{
	static int	items_count = 0;
	static int	count = 0;

	map->player_y += y_move;
	map->player_x += x_move;
	mlx_destroy_image(map->m_pack->mlx, map->m_pack->player);
	image_2_map(map, map->m_pack->player, map->player_x, map->player_y);
	ft_putstr_fd("Movements: ", 1);
	ft_putnbr_fd(++count, 1);
	if (map->split_map[map->player_y][map->player_x] == 'C')
		item_collected(map, &items_count);
	else if (map->split_map[map->player_y][map->player_x] == 'E'
		&& items_count == map->items)
	{
		//(void)write(1, "\033[0;33m", 7);
		ft_putstr_fd("Well done !", 1);
		mlx_destroy_window(map->m_pack->mlx, map->m_pack->win);
		//(void)write(1, "\033[0m", 5);
		return ;
	}
}

static int	key_hook(int keycode, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keycode == 65307)
		mlx_destroy_window(map->m_pack->mlx, map->m_pack->win);
	if (keycode == 119 && map->split_map[map->player_y
		- 1][map->player_x] != '1')
		movement(map, 0, -1);
	else if (keycode == 100 && map->split_map[map->player_y][map->player_x
		+ 1] != '1')
		movement(map, 1, 0);
	else if (keycode == 115 && map->split_map[map->player_y
		+ 1][map->player_x] != '1')
		movement(map, 0, 1);
	else if (keycode == 97 && map->split_map[map->player_y][map->player_x
		- 1] != '1')
		movement(map, -1, 0);
	return (0);
}

static void	render_map(t_map *map, int x, int y)
{
	while (map->split_map[y])
	{
		while (map->split_map[y][x])
		{
			if (map->split_map[y][x] == '1')
				image_2_map(map, map->m_pack->wall, x, y);
			else if (map->split_map[y][x] == '0' || map->split_map[y][x] == 'C'
				|| map->split_map[y][x] == 'P')
				image_2_map(map, map->m_pack->floor, x, y);
			else if (map->split_map[y][x] == 'E')
			{
				image_2_map(map, map->m_pack->exit_open, x, y);
				image_2_map(map, map->m_pack->exit_close, x, y);
			}
			if (map->split_map[y][x] == 'P')
				image_2_map(map, map->m_pack->player, x, y);
			if (map->split_map[y][x] == 'C')
				image_2_map(map, map->m_pack->items, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	graphics(t_map *map)
{
	t_pack m_pack;
	int width;

	map->m_pack = &m_pack;
	width = (int)ft_strlen(map->split_map[0]);
	map->m_pack->mlx = mlx_init();
	if (!map->m_pack->mlx)
		exit_free(map, "Error initializing MLx!");
	map->m_pack->win = mlx_new_window(map->m_pack->mlx, width * IMG_SIZE ,
			map->height * IMG_SIZE, "so_long");
    if (!map->m_pack->win)
		exit_free(map, "Error creating MLX window!");
	map->m_pack->wall = set_image(map, WALL);
	map->m_pack->floor = set_image(map, FLOOR);
	map->m_pack->items = set_image(map, ITEMS);
	map->m_pack->player = set_image(map, GHOST);
	map->m_pack->exit_close = set_image(map, CLOSED);
	map->m_pack->exit_open = set_image(map, OPENED);
    
	render_map(map, 0, 0);
	mlx_key_hook(map->m_pack->win, &key_hook, map);
    mlx_hook(map->m_pack->win, 17, 0, (void *)clean_exit, map);
	mlx_loop(map->m_pack->mlx);
}