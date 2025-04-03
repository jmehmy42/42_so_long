/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:01:54 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/03 09:57:17 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clean_exit(t_map *map)
{
	if (map->m_pack->win)
		mlx_destroy_window(map->m_pack->mlx, map->m_pack->win);
	if (map->m_pack->mlx)
	{
		mlx_destroy_display(map->m_pack->mlx);
		free(map->m_pack->mlx);
	}
	exit(0);
}

static int	ber_verify(char *path)
{
	int	len;

	len = 0;
	while (path[len])
		len++;
	if ((len > 4) && (path[len - 4] == '.') && (path[len - 3] == 'b' || path[len
			- 3] == 'B') && (path[len - 2] == 'e' || path[len - 2] == 'E')
		&& (path[len - 1] == 'r' || path[len - 1] == 'R'))
		return (0);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	s_map;

	if (argc != 2)
		return (ft_error("Error more or less than one arguments \n"));
	if (ber_verify(argv[1]) == -1)
		return (ft_error("Error not a .ber file\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error("Error opening file or no file found\n"));
	s_map.map = read_map(fd);
	close(fd);
	if (!s_map.map)
		return (ERROR);
	if (verify_map(&s_map) == ERROR)
		return (ERROR);
	graphics(&s_map);
	close(fd);
	return (0);
}
