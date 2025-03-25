/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:32:00 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/23 19:49:10 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    free_map (t_data *data)
{
    int i;

    if (data->map.map == NULL)
        return ;
    i = 0;
    while (data->map.map[i])
    {
        if (data->map.map[i])
            free (data->map.map[i]);
        i++;
    }
    if (data->map.map)
        free(data->map.map);
}

void    free_all (t_data *data, int code)
{
    if (code == -4)
        return ;
    free_map(data);
    if(data->gnl.line != NULL && code != -3)
        free(data->gnl.line);
    if(data->gnl.leftover != NULL)
        free(data->gnl.leftover);
    if (data->wall.img != NULL)
        mlx_destroy_image(data->window.mlx, data->wall.img);
    if (data->collect.img != NULL)
        mlx_destroy_image(data->window.mlx, data->collect.img);
    if (data->player.img != NULL)
        mlx_destroy_image(data->window.mlx, data->player.img);
    if (data->exit.img != NULL)
        mlx_destroy_image(data->window.mlx, data->exit.img);
    if (data->window.window != NULL)
    {
        mlx_loop_end(data->window.window);
        mlx_destroy_window(data->window.mlx, data->window.window);
    }
    if (data->window.mlx != NULL)
    {
        mlx_destroy_display(data->window.mlx);
        free(data->window.mlx);
    }
    
}

void    ft_return(t_data *data, int code)
{
    if (code == 0 || code == -2 || code == -3 || code == -4
        || code == -5)
        {
            if(code == -2 || code == -3 )
                ft_putst("Error\nInvalid map\n");
            if (code == -4)
                ft_putstr("Error\nPas de Fichier\n");
            if (code == -5)
                ft_putstr("Error\nFormat du fichier invalide\n");
            free_all(data, code);
            exit(0);
        }
        if (code == -1)
        {
            ft_putstr("Error\n");
            if (errno != 0)
                perror("so_long ");
            else
                ft_putstr("fichier vide\n");
            free_all(data, code);
            exit(-1);
        }
}