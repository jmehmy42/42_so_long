/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:49:30 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/03 14:31:30 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	item_collected(t_map *map, int *items_count)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(*items_count)++;
	if (*items_count == map->items)
	{
	 	image_2_map(map, map->m_pack->exit_open, map->x_exit, map->y_exit);
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->exit_close);
		map->m_pack->exit_close = NULL;
	}
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

static void	movement(t_map *map, int x_move, int y_move)
{
	static int	items_count = 0;
	static int	count = 0;
	int new_x = map->player_x + x_move;
	int new_y = map->player_y + y_move;

	// Prevent moving into walls
	if (map->split_map[new_y][new_x] == '1')
		return;

	// Check if player is on an item and collect it
	if (map->split_map[new_y][new_x] == 'C')
		item_collected(map, &items_count);

	// Check if player reaches the exit and has collected all items
	if (map->split_map[new_y][new_x] == 'E')
	{
		if ( items_count == map->items)
		{
			ft_putstr_fd("\n✨ Well done! You have completed the game. ✨\n", 1);
			delete_textures(map);
			free_string(map->split_map);
			exit(0);
		}
		else
		{
			ft_putstr_fd("You Must Collect all items before exiting\n", 1);
			return ;
		}
	}

	// Update player position
	map->split_map[map->player_y][map->player_x] = '0';  // Clear previous position
	map->player_x = new_x;
	map->player_y = new_y;
	map->split_map[map->player_y][map->player_x] = 'P';  // Mark new position

	// Update images on the screen
	image_2_map(map, map->m_pack->floor, map->player_x - x_move, map->player_y - y_move);
	image_2_map(map, map->m_pack->player, map->player_x, map->player_y);

	// Display movement count
	ft_putstr_fd("Movements: ", 1);
	ft_putnbr_fd(++count, 1);
	ft_putchar_fd('\n', 1);
	if (map->split_map[map->player_y][map->player_x] == 'C')
		item_collected(map, &items_count);
}

static int	key_hook(int keycode, t_map *map)
{
	if(!map)
		return (0);
	if (keycode == 65307)
	{ 
		ft_putstr_fd("Game closed.\n", 1);
		delete_textures(map);
		free_string(map->split_map);
		exit(0);
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
				map->x_exit = x;
				map->y_exit = y;
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
	{
		ft_putstr_fd("Error initializing MLX\n", 1);
		free(map->m_pack);
		free_string(map->split_map);
		exit(ERROR);
	}
	map->m_pack->win = mlx_new_window(map->m_pack->mlx, width * IMG_SIZE ,
			map->height * IMG_SIZE, "so_long");
    if (!map->m_pack->win)
	{
		ft_putstr_fd("Error creating MLX window\n", 1);
		free(map->m_pack);
		free_string(map->split_map);
		if (map->m_pack->win)
			mlx_destroy_window(map->m_pack->mlx, map->m_pack->win);
		if (map->m_pack->mlx)
		{
			mlx_destroy_display(map->m_pack->mlx);
			free(map->m_pack->mlx);
		}
		exit(ERROR);
	}
	map->m_pack->wall = set_image(map, WALL);
	map->m_pack->floor = set_image(map, FLOOR);
	map->m_pack->items = set_image(map, ITEMS);
	map->m_pack->player = set_image(map, GHOST);
	map->m_pack->exit_close = set_image(map, CLOSED);
	map->m_pack->exit_open = set_image(map, OPENED);
    
	render_map(map, 0, 0);
	mlx_hook(map->m_pack->win, 2, 1L << 0,  key_hook, map);
    mlx_hook(map->m_pack->win, 17, 0, (void *)clean_exit, map);
	mlx_loop(map->m_pack->mlx);
}
