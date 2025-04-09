/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:42:25 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 13:42:41 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_minium_size(t_map *s_map, int y, int len)
{
	if (++y < 3 || len < 3)
	{
		ft_error("Error: Rectangle too small\n");
		return ;
	}
	s_map->height = y;
}

static int	dimension_check(t_map *s_map, int x, int y, int len)
{
	int	line_len;

	len = ft_strlen(s_map->split_map[0]);
	while (s_map->split_map[0][x])
		if (s_map->split_map[0][x++] != '1')
			return (ft_error("Error: top wall not close with 1s\n"));
	y = 1;
	while (s_map->split_map[y + 1])
	{
		line_len = ft_strlen(s_map->split_map[y]);
		if (line_len != len)
			return (ft_error("Error: not a rectangle\n"));
		if (s_map->split_map[y][0] != '1' || s_map->split_map[y][len
			- 1] != '1')
			return (ft_error("Error: side wall not close with 1\n"));
		y++;
	}
	x = 0;
	while (x < len)
		if (s_map->split_map[y][x++] != '1')
			return (ft_error("Error: bottom wall not close with 1\n"));
	if ((int)ft_strlen(s_map->split_map[y]) != len)
		return (ft_error("Error: bottom row incorrect\n"));
	check_minium_size(s_map, y, len);
	return (0);
}

static void	path_algo(t_map *s_map, int y, int x)
{
	if (s_map->copy[y][x] == 'C')
		s_map->copy_items++;
	else if (s_map->copy[y][x] == 'E')
		s_map->copy_exit++;
	s_map->copy[y][x] = 'X';
	if (s_map->copy[y][x + 1] != '1' && s_map->copy[y][x + 1] != 'X')
		path_algo(s_map, y, x + 1);
	if (s_map->copy[y][x - 1] != '1' && s_map->copy[y][x - 1] != 'X')
		path_algo(s_map, y, x - 1);
	if (s_map->copy[y + 1][x] != '1' && s_map->copy[y + 1][x] != 'X')
		path_algo(s_map, y + 1, x);
	if (s_map->copy[y - 1][x] != '1' && s_map->copy[y - 1][x] != 'X')
		path_algo(s_map, y - 1, x);
	return ;
}

static int	path_check(t_map *s_map)
{
	s_map->copy = ft_split(s_map->map, '\n');
	if (!s_map->copy)
		return (-1);
	get_positions(s_map);
	s_map->copy_items = 0;
	s_map->copy_exit = 0;
	path_algo(s_map, s_map->player_y, s_map->player_x);
	free_string(s_map->copy);
	if (s_map->copy_exit != 1 || s_map->copy_items != s_map->items)
		return (ft_error("Error: Can't collect all collectibles\n"));
	return (0);
}

int	verify_map(t_map *s_map)
{
	s_map->items = 0;
	s_map->exit = 0;
	s_map->start = 0;
	if (s_map->map == NULL)
	{
		ft_error("Error: map is invalid\n");
		return (free_mem(s_map->map, NULL));
	}
	if (ft_strlen(s_map->map) >= 1000)
	{
		ft_error("Error: map is too big\n");
		return (free_mem(s_map->map, NULL));
	}
	if (chars_check(s_map, "01PEC\n") == -1)
		return (free_mem(s_map->map, NULL));
	s_map->split_map = ft_split(s_map->map, '\n');
	if (!s_map->split_map)
		return (free_mem(s_map->map, NULL));
	if ((dimension_check(s_map, 0, 1, 0) == -1) || (path_check(s_map) == -1))
		return (free_string(s_map->split_map), free_mem(s_map->map, NULL));
	free(s_map->map);
	return (0);
}
