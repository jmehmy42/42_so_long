/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_even.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:45:07 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/24 21:01:00 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    print_count(t_data *data)
{
    ft_putstr("Nombre de coup : ");
    ft_putnbr(data->move);
    ft_putstr("\n");
}

int     check_case(t_data *data, int i, int j)
{
    if (data->map.map[i][j] == '1')
        return (1);
    if (data->map.map[i][j] == 'C')
     data->collect.count--;
    if (data->map.map[j][i] == 'E' && data->collect.count == 0)
    {
        data->map.map[j][i] = 'P';
        mlx_destory_image(data->window.mlx, data->player.img);
        data->player.img = mlx_xpm_file_to_image(data->window.mlx, ".textures/onishock.xpm", &data->player.width, &data->player.height);
        data->move++;
        print_count(data);
        print_map(data);
        ft_return(data, 0);
    }
    else if (data->map.map[j][i] == 'E' && data->collect.count != 0)
        data->map.map[j][i] == 'F';
    else
        data->map.map[j][i] = 'P';
    data->player.x = i;
    data->player.y = j;
    return (0);
}

int move_player(int keycode, t_data *data)
{
    int c;
    int i;
    int j;

    i = data->player.x;
    j = data->player.y;
    c = 0;
    if (keycode == 100)
        c = check_case(data, data->player.x + 1, data->player.y);
    if (keycode == 97)
        c = check_case(data , data->player.x -1, data->player.y);
        if (keycode == 115)
		c = check_case(data, data->player.x, data->player.y + 1);
	if (keycode == 119)
		c = check_case(data, d->player.x, data->player.y - 1);
	if (c == 0)
	{
		if (data->map.map[j][i] == 'F')
			data->map.map[j][i] = 'E';
		else
			data->map.map[j][i] = '0';
		data->move++;
		print_count(data);
	}
	return (0);
    
}

int	handle_close(t_data *d)
{
	ft_return(d, 0);
	return (0);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 65307)
		ft_return(data, 0);
	if (keycode == 100 || keycode == 97 || keycode == 115 || keycode == 119)
	{
		move_player(keycode, data);
		mlx_clear_window(data->window.mlx, data->window.window);
		print_map(data);
	}
	return (0);
}