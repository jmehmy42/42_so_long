/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:43:54 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 18:48:06 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int show_movecount_in_win(t_window *mlx)
{
    char *move_count;

    move_count = ft_itoa((*mlx).count_move);
    mlx_string_put((*mlx).mlx, (*mlx).mlx_win, 10, 20, 0x00FFFFFF, move_count);
    free(move_count);
    return (0);
}

int exit_game(t_window *mlx)
{
    if ((*mlx).map)
        ft_lstclear(&(*mlx).map, free);
    mlx_destroy_window((*mlx).mlx, (*mlx).mlx_win);
    free((*mlx).mlx);
    exit(0);
}