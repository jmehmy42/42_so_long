/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:18:37 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 12:29:22 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int main (int ac, char **av)
{
    t_data data;
    int i;

    if(ac != 2)
        ft_return(&data, -4);
    i = ft_init(av[1], &data);
    if (i != 0)
        ft_return(&data, i);
    ft_return(&data, 0);
    return (0);
}