/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:05:41 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 12:32:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	unlock_exit(t_map *map)
{
	map->open_door = 1;
	render_map(map, 0, 0);
	image_2_map(map, map->m_pack->exit_open, map->x_exit, map->y_exit);
	mlx_destroy_image(map->m_pack->mlx, map->m_pack->exit_close);
	map->m_pack->exit_close = NULL;
}

void	item_collected(t_map *map, int *items_count)
{
	int	x;
	int	y;

	y = 0;
	(*items_count)++;
	if (*items_count == map->items)
		unlock_exit(map);
	mlx_destroy_image(map->m_pack->mlx, map->m_pack->items);
	map->m_pack->items = set_image(map, ITEMS);
	map->split_map[map->player_y][map->player_x] = '0';
	while (map->split_map[y])
	{
		x = 0;
		while (map->split_map[y][x])
		{
			if (map->split_map[y][x] == 'C')
				image_2_map(map, map->m_pack->items, x, y);
			x++;
		}
		y++;
	}
}

static void	update_player_position(t_map *map, int new_x, int new_y)
{
	map->split_map[map->player_y][map->player_x] = map->tile_under_player;
	if (map->split_map[new_y][new_x] == 'E')
		map->tile_under_player = 'E';
	else
		map->tile_under_player = '0';
	map->player_x = new_x;
	map->player_y = new_y;
	map->split_map[map->player_y][map->player_x] = 'P';
}

static void	render_movement(t_map *map, int x, int y, int *count)
{
	image_2_map(map, map->m_pack->floor, map->player_x - x, map->player_y - y);
	image_2_map(map, map->m_pack->player, map->player_x, map->player_y);
	if (map->open_door)
		draw_exit(map, map->x_exit, map->y_exit);
	ft_printf("Movements: %d\n", ++count);
}

void	movement(t_map *map, int x, int y)
{
	static int	items_count = 0;
	static int	count = 0;
	int			new_x;
	int			new_y;

	new_x = map->player_x + x;
	new_y = map->player_y + y;
	map->player_exit = (map->split_map[new_y][new_x] == 'E');
	if (map->split_map[new_y][new_x] == '1')
		return ;
	if (map->split_map[new_y][new_x] == 'C')
		item_collected(map, &items_count);
	if (map->split_map[new_y][new_x] == 'E')
	{
		if (items_count == map->items)
		{
			ft_putstr_fd("\n✨ Well done! You have completed the game. ✨\n", 1);
			del_and_free(map, 1);
		}
		else
			ft_putstr_fd("collect all items before exit\n", 1);
	}
	update_player_position(map, new_x, new_y);
	render_movement(map, x, y, &count);
}
