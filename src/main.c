/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:01:54 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 14:41:45 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	close_window(t_map *map)
{
	delete_textures(map);
	free(map->m_pack);
	free_string(map->split_map);
	exit(0);
}

void	free_mlx(t_map *map)
{
	ft_putstr_fd("Error MLX initializing fail\n", 1);
	free(map->m_pack);
	free_string(map->split_map);
	exit(ERROR);
}

void	load_textures(t_map *map)
{
	map->m_pack->wall = set_image(map, WALL);
	map->m_pack->floor = set_image(map, FLOOR);
	map->m_pack->items = set_image(map, ITEMS);
	map->m_pack->player = set_image(map, GHOST);
	map->m_pack->exit_close = set_image(map, CLOSED);
	map->m_pack->exit_open = set_image(map, OPENED);
}

static int	ber_verify(char *path)
{
	int	len;

	len = 0;
	if (!path)
		return (1);
	while (path[len])
		len++;
	if ((len > 4) && (path[len - 4] == '.') && (path[len - 3] == 'b')
		&& (path[len - 2] == 'e') && (path[len - 1] == 'r'))
		return (0);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	s_game;

	if (argc != 2)
		return (ft_error("Error more or less than one arguments \n"));
	if (ber_verify(argv[1]) == -1)
		return (ft_error("Error not a .ber file\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error("Error opening file or no file found\n"));
	if (read_map(&s_game, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (verify_map(&s_game) == -1)
		return (ERROR);
	graphics(&s_game);
	return (0);
}
