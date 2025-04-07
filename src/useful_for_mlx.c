/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_for_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:28:53 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/07 11:00:11 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	delete_textures(t_map *map)
{
	if (!map || !map->m_pack)
		return ;
	if (map->m_pack->wall)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->wall);
	if (map->m_pack->floor)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->floor);
	if (map->m_pack->player)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->player);
	if (map->m_pack->items)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->items);
	if (map->m_pack->exit_close)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->exit_close);
	if (map->m_pack->exit_open)
		mlx_destroy_image(map->m_pack->mlx, map->m_pack->exit_open);
	if (map->m_pack->win)
		mlx_destroy_window(map->m_pack->mlx, map->m_pack->win);
	if (map->m_pack->mlx)
	{
		mlx_destroy_display(map->m_pack->mlx);
		free(map->m_pack->mlx);
	}
	map->m_pack->mlx = NULL;
}

void	del_and_free(t_map *map, int code)
{
	delete_textures(map);
	free(map->m_pack);
	free_string(map->split_map);
	if (code != 0)
		exit(0);
	else
		exit(ERROR);
}

void	*set_image(t_map *map, char *path)
{
	int		width;
	int		height;
	void	*img;

	img = mlx_xpm_file_to_image(map->m_pack->mlx, path, &width, &height);
	if (!img)
	{
		ft_putstr_fd("Error loading image\n", 2);
		del_and_free(map, 1);
	}
	return (img);
}

void	image_2_map(t_map *map, void *image, int x, int y)
{
	if (mlx_put_image_to_window(map->m_pack->mlx, map->m_pack->win, image, x
			* IMG_SIZE, y * IMG_SIZE) == -1)
	{
		ft_putstr_fd("Error displaying image\n", 2);
		del_and_free(map, 1);
	}
}
