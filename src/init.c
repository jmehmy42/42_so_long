/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:52:22 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/24 16:14:51 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    put_player(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->map.map[j][i] != 'P' && data->map.map[j][i] &&
            data <= data->map.ord_y)
            {
                if (i == data->map.ord_x)
                {
                    j++;
                    i = 0;
                }
                i++;
            }
            data->player.y = j;
            data->player.x = i;
}

int init_img(t_data *data)
{
    data->wall.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/wall.xpm",
    &data->wall.width, &data->wall.height);
    data->collect.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/collect.xpm",
        &data->collect.width, &data->collect.height);
    data->player.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/player.xpm",
        &data->player.width, &data->player.height);
    data->exit.img = mlx_xpm_file_to_image(data->window.mlx, "./textures/exit.xpm",
        &data->exit.width, &data->exit.height);
    if (data->wall.img == NULL || data->exit.img == NULL || data->player.img == NULL || data->collect.img == NULL)
        return (-1);
    print_map(data);
    return (0);
}

int init_window(t_data *data)
{
    data->window.mlx = mlx_init();
    if(!data->window.mlx)
        return (-1);
    mlx_get_screen_size(data->window.mlx, &(data->window.width), &(data->window.height));
    if (data->window.width < (data->map.ord_x * 40) && data->window.height < (data->map.ord_y *40))
data->window.window = mlx_new_window(data->window.mlx, data->window.width, (data->window.height - 80), "so_long");
    else if
        ( data->window.width < (data->map.ord_x * 40))
        data->window.window = mlx_new_window(data->window.mlx, data->window.width, (((data->map.ord_y + 1) * 40) + 1), "so_long");
    else if
        (data->window.height < (data->map.ord_y * 40))
        data->window.window = mlx_new_window(data->window.mlx, ((data->map.ord_x * 40) + 1), data->window.height, "so_long");
    else
        data->window.window = mlx_new_window(data->window.mlx, ((data->map.ord_x * 40) + 1), (((data->map.ord_y + 1) * 40) + 1), "so_long");
    
    if (!data->window.window)
        return (-1);
    if (init_img(data) == -1)
        return (-1);
    mlx_hook(data->window.window, 3, 1L << 1, handle_key, data);
    mlx_hook(data->window.window, 17, 1L<< 2, handle_close, data);
    mlx_loop(data->window.mlx);
    return (0);
}
void    set_zero(t_data *data)
{
    errno = 0;
    data->window.mlx = NULL;
    data->window.window = NULL;
    data->wall.img = NULL;
    data->collect.img = NULL;
    data->collect.count = 0;
    data->player.img = NULL;
    data->player.count = 0;
    data->exit.img = NULL;
    data->exit.count = 0;
    data->map.map = NULL;
    data->player.x = 0;
    data->player.y = 0;
    data->gnl.leftover = NULL;
    data->gnl.line = NULL;
    data->move = 0;
    data->window.width = 0;
    data->window.height = 0;
    data->map.start_h = 0;
    data->map.start_w = 0;
    data->map.end_h = 0;
    data->map.end_w = 0;
    data->map.map = NULL;
}

int ft_init(char *av1, t_data *data)
{
    int i;

    set_zero(data);
    i = check_map(av1, data);
    if (i != 0)
        return (i);
    put_player(data);
    if (init_window(data) == -1)
        return (-1);
    return (0);
}