/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:42:25 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/04 22:13:29 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	chars_check(t_map *s_map, char *str)
{
	int	i;

	i = 0;
	while (s_map->map[i])
	{
		if (char_finder(str, s_map->map[i]) >= 0)
		{
			if (s_map->map[i] == 'P')
				s_map->start++;
			else if (s_map->map[i] == 'C')
				s_map->items++;
			else if (s_map->map[i] == 'E')
				s_map->exit++;
			else if ((s_map->map[0] == '\n') || (s_map->map[i] == '\n'
					&& (s_map->map[i + 1] == '\n' || s_map->map[i + 1] == 0)))
				return (ft_error("Error: Consecutive newlines or at end\n"));
			i++;
		}
		else
			return (ft_error("Error: Character other than 01PCE\n"));
	}
	if (s_map->start != 1 || s_map->items == 0 || s_map->exit != 1)
		return (ft_error("Error: Wrong quantity of start/collectibles/exit\n"));
	return (0);
}

static int	dimension_check(t_map *s_map, int x, int y, int len)
{
	while (s_map->split_map[0][len])
	{
		if (s_map->split_map[0][len] != '1')
			return (ft_error("Error: Not rectangle/not using 1 outlines\n"));
		len++;
	}
	while (s_map->split_map[y + 1])
	{
		if (s_map->split_map[y][0] != '1' || s_map->split_map[y][len - 1] != '1'
			|| ((int)ft_strlen(s_map->split_map[y]) != len))
			return (ft_error("Error:not a rectangle/not using 1 outlines\n"));
		y++;
	}
	while (s_map->split_map[y][x])
	{
		if (s_map->split_map[y][x] != '1'
			|| ((int)ft_strlen(s_map->split_map[y]) != len))
			return (ft_error("Error:not a rectangle/not using 1 outlines\n"));
		x++;
	}
	if (++y < 3 || len < 3)
		return (ft_error("Error: Rectangle too small\n"));
	s_map->height = y;
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
	if (ft_strlen(s_map->map) >= 400)
	{
		ft_error("Error: map is too big\n");
		return (free_mem(s_map->map, NULL));
	}
	if (chars_check(s_map, "01PEC\n") == ERROR)
		return (free_mem(s_map->map, NULL));
	s_map->split_map = ft_split(s_map->map, '\n');
	if (!s_map->split_map)
		return (free_mem(s_map->map, NULL));
	if ((dimension_check(s_map, 0, 1, 0) == ERROR)
		|| (path_check(s_map) == ERROR))
	{
		free_string(s_map->split_map);
		return (free_mem(s_map->map, NULL));
	}
	free(s_map->map);
	return (0);
}
