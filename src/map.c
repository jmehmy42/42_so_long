/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:51:34 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 18:59:53 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void    draw_background (t_window *mlx, char *line, int line_count)
{
    int x;
    int y;

    x = 0;
    y = line_count;
    while(*line)
    {
        draw_floor(mlx, x * 50, y * 50);
        line++;
        x++;
    }
}

void draw_img_to_map (t_window *mlx, char *line, int line_count)
{
    int x;
    int y;

    x = 0;
    y = line_count;
    while (*line)
    {
        if (*line == '0')
            draw_floor(mlx, x * 50, y * 50);
        else if (*line == '1')
            draw_wall(mlx, x * 50, y * 50);
        else if (*line == 'C')
            draw_collectible(mlx, x * 50, y * 50);
        else if (*line == 'E')
            draw_exit(mlx, x * 50, y * 50);
        else if (*line == 'P')
            draw_player(mlx, x * 50, y * 50);
        line++;
        x++;
    }
}

void    create_map(t_window *mlx, t_list *map)
{
    t_list *f_list;
    t_list *s_list;
    int i;
    int map_height;

    i = 0;
    f_list = map;
    s_list = map;
    map_height = ft_lstsize(map);
    while ( i < map_height)
    {
        draw_background(mlx, f_list->content, i);
        f_list = f_list->next;
        i++;
    }
    i = 0;
    while (i <map_height)
    {
        draw_img_to_map(mlx, s_list->content, i);
        s_list = s_list->next;
        i++;
    }
}
