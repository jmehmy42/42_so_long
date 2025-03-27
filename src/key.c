/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:23:03 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 18:42:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int handle_key_press(int key, t_window *mlx)
{
    if (key == UP || key == LEFT || key == RIGHT  || key == DOWN)
    {
        move_player(mlx, key);
        create_map(mlx, (*mlx).map);
    }
    else if (key == ESC)
        exit_game(mlx);
    return (0);
}