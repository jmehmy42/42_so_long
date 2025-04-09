/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:49:30 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 16:08:05 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_hook(int keycode, t_map *map)
{
	if (!map)
		return (0);
	if (keycode == 65307)
	{
		ft_putstr_fd("Game closed.\n", 1);
		del_and_free(map, 1);
	}
	if (keycode == 119 || keycode == 65362)
		movement(map, 0, -1);
	else if (keycode == 100 || keycode == 65363)
		movement(map, 1, 0);
	else if (keycode == 115 || keycode == 65364)
		movement(map, 0, 1);
	else if (keycode == 97 || keycode == 65361)
		movement(map, -1, 0);
	return (0);
}

void	render_map(t_map *map, int x, int y)
{
	while (map->split_map[y])
	{
		x = 0;
		while (map->split_map[y][x])
		{
			if (map->split_map[y][x] == '1')
				image_2_map(map, map->m_pack->wall, x, y);
			else if (map->split_map[y][x] == '0' || map->split_map[y][x] == 'C'
				|| map->split_map[y][x] == 'P')
				image_2_map(map, map->m_pack->floor, x, y);
			else if (map->split_map[y][x] == 'E')
				draw_exit2(map, x, y);
			if (map->split_map[y][x] == 'P')
				image_2_map(map, map->m_pack->player, x, y);
			if (map->split_map[y][x] == 'C')
				image_2_map(map, map->m_pack->items, x, y);
			x++;
		}
		y++;
	}
}

void	graphics(t_map *map)
{
	int	width;

	map->open_door = 0;
	map->player_exit = 0;
	map->current_tile = '0';
	map->x_exit = -1;
	map->y_exit = -1;
	map->m_pack = ft_calloc(1, sizeof(t_pack));
	width = (int)ft_strlen(map->split_map[0]);
	map->m_pack->mlx = mlx_init();
	if (!map->m_pack->mlx)
		free_mlx(map);
	map->m_pack->win = mlx_new_window(map->m_pack->mlx, width * IMG_SIZE,
			map->height * IMG_SIZE, "so_long");
	if (!map->m_pack->win)
		free_mlx_window(map);
	load_textures(map);
	render_map(map, 0, 0);
	mlx_hook(map->m_pack->win, 2, 1L << 0, key_hook, map);
	mlx_hook(map->m_pack->win, 17, 0, (void *)close_window, map);
	mlx_loop(map->m_pack->mlx);
}
