/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_for_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:28:53 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/02 23:21:53 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	delete_textures(t_map *map)
{
	if (!map || !map->m_pack)
		return;

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
	map->m_pack->mlx = NULL;  // Prevent further use of freed memory
}

void exit_free(t_map *map)
{
    if (!map)  // If map is NULL, do nothing
        return;

    delete_textures(map);  // Assuming delete_textures handles NULL cases safely

    if (map->split_map)
    {
        printf("Freeing split_map\n");
        free_string(map->split_map);
        map->split_map = NULL;
    }
    // if (map->copy)
    // {
    //     printf("Freeing copy\n");
    //     free_string(map->copy);
    //     map->copy = NULL;
    // }
    // if (map->map)
    // {
    //     printf("Freeing map\n");
    //     safe_free((void **)&map->map); // Free only if needed
    // }

    //safe_free((void **)&map); // Free map itself

	//exit(ERROR);
}


void	*set_image(t_map *map, char *path)
{
	int		width;
	int		height;
	void	*img;

	img = mlx_xpm_file_to_image(map->m_pack->mlx, path, &width, &height);
	if (!img)
	{
		ft_putstr_fd("Error loading image\n", 1);
		exit_free(map);
		exit(ERROR);
	}
	// if (width != IMG_SIZE || height != IMG_SIZE)
	// 	exit_free(map, "Error: Image size incoorect!");
	return (img);
}

void	image_2_map(t_map *map, void *image, int x, int y)
{
	if (mlx_put_image_to_window(map->m_pack->mlx, map->m_pack->win, image, x
			* IMG_SIZE, y * IMG_SIZE) == -1)
	{
		ft_putstr_fd("Error displaying image\n", 1);
		exit_free(map);
		exit(ERROR);
	}
}
