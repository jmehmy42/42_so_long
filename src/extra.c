/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:31:55 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 16:14:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	draw_exit(t_map *map, int x, int y)
{
	if (map->open_door)
	{
		image_2_map(map, map->m_pack->exit_open, x, y);
	}
	else
		image_2_map(map, map->m_pack->exit_close, x, y);
}

void	draw_exit2(t_map *map, int x, int y)
{
	map->x_exit = x;
	map->y_exit = y;
	if (map->open_door)
		image_2_map(map, map->m_pack->exit_open, x, y);
	else
		image_2_map(map, map->m_pack->exit_close, x, y);
}
