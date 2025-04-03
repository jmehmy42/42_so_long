/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:16:33 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/03 15:00:49 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_positions(t_map *s_map)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	while (s_map->split_map[y])
	{
		x = char_finder(s_map->split_map[y], 'P');
		if (x != -1)
		{
			s_map->player_x = x;
			s_map->player_y = y;
		}
		y++;
	}
}

int	char_finder(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	free_mem(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ERROR);
}

int	ft_error(char *message)
{
	ft_putstr_fd(message, 1);
	return (ERROR);
}

void error_mlx_window(t_map *map)
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
