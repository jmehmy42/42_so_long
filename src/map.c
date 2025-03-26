/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:01:50 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 18:18:08 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    put_line(char *str, int y, t_data *data, int i)
{
    int j;

    j = data->map.start_w;
    if(data->map.end_w == 0)
        data->map.end_w = data->map.ord_x;
    while (str[j] && str [j]  != '\n' && j <= data->map.end_w)
    {
        if (str[j] == '1')
            mlx_put_image_to_window(data->window.mlx, data->window.window, data->wall.img, (i * 40), (y * 40));
        if (str[j] == 'P')
            mlx_put_image_to_window(data->window.mlx, data->window.window, data->player.img, (i * 40), (y * 40));
        if (str[j] == 'E')
            mlx_put_image_to_window(data->window.mlx, data->window.window, data->exit.img, (i * 40), (y * 40));
        if (str[j] == 'F')
           mlx_put_image_to_window(data->window.mlx, data->window.window, data->collect.img, (i * 40), (y * 40));
        if(str[j] == 'c')
            mlx_put_image_to_window(data->window.mlx, data->window.window, data->collect.img, (i * 40), (y * 40));
        j++;
        i++;           
    }
}

void scrolling_w(t_data *data)
{
    int mid;
    int nb;

    nb = data->window.width / 40;
    mid = nb / 2;
    data->map.start_w = data->player.x - mid;
    data->map.end_w = data->player.x + mid;
    if (data->map.start_w < 0)
    {
        data->map.start_w = 0;
        data->map.end_w = nb;
    }
    if (data->map.end_w > data->map.ord_x)
    {
        data->map.start_w = data->map.ord_x - nb;
        data->map.end_w = data->map.ord_x;
    }
}

void scrolling_h (t_data *data)
{
    int mid;
    int nb;

    nb = (data->window.height - 80) / 40;
    mid = nb / 2;
    data->map.start_h = data->player.y - mid;
    data->map.end_h = data->player.y + mid;
    if (data->map.start_h < 0)
    {
        data->map.start_h = 0;
        data->map.end_h = nb;
    }
    if (data->map.end_h > data->map.ord_y)
    {
        data->map.start_h = data->map.ord_y - nb + 1;
        data->map.end_h = data->map.ord_y;
    }
}

void print_map (t_data *data)
{
    int i;
    int j;
    int k;

    if (data->window.width > (data->map.ord_x * 40))
        scrolling_w(data);
    if (data->window.height < (data->map.ord_y * 40))
        scrolling_h(data);
    k = 0;
    j = data->map.start_h;
    if (data->map.end_h == 0)
        data->map.end_h = data->map.ord_y;
    while (data->map.map[j] && j <= data->map.end_h)
    {
        i = 0;
        put_line(data->map.map[j], k, data, i);
        k++;
        j++;
    }
}