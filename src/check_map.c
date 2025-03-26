/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:59:24 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 22:32:55 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int check_only_one(char *str, int x)
{
    int i;

    i = 0 ;
    while (str[i] && str[i] == '1')
        i++;
    if (1 != x)
        return (-2);
    return (0);
}

int parse_map (char *av1, t_data *data)
{
    int i;
    int fd;

    fd = open (av1, O_RDONLY);
    if(!fd)
        return (-1);
    data->map.map = ft_calloc(data->map.ord_y + 2, sizeof(char *));
    if(!data->map.map)
        return (-1);
    i = 0;
    while (i <= data->map.ord_y)
    {
        data->map.map[i] = get_next_line(fd, 100, data);
        if (!data->map.map[i])
            return (-1);
        if ( i == 0 || i == data->map.ord_y)
        {
            if (check_only_one(data->map.map[i], data->map.ord_x) != 0)
                return (-3);
        }
        i++;
    }
    get_next_line(fd, 100, data);
    close(fd);
    return (0);    
}

int check_line (char *str, t_data *data)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\n')
    {
        if ((i == 0 || i == data->map.ord_x) && str[i] != '1')
            return (-2);
        else if (str[i] == 'C')
            data->collect.count++;
        else if (str[i] == 'E')
            data->exit.count++;
        else if (str[i] == 'P')
            data->player.count++;
        else
        {
            if (str[i] != '0' && str[i] !=  '1' && str[i] != '\n')
                return (-2);
        }
        i++;
    }
    if (i != data->map.ord_x && str[0] != '\n')
        return (-2);
    return (0);
}

int check_reactangle(char *av1, t_data *data, int ret, int fd)
{
    char *str;

    fd = open(av1, O_RDONLY);
    if (fd == -1)
        return (-1);
    str = get_next_line(fd, 100, data);
    if (!str)
    {
        close(fd);
        return (-1);
    }
    while (str[data->map.ord_x] && str[data->map.ord_x] != '\n')
        data->map.ord_x++;
    while (str != NULL)
    {
        free(str);
        str = get_next_line(fd, 100, data);
        if (str == NULL)
            break;
        ret = check_line(str, data);
        if (ret != 0)
            return (ret);
        if (str[0] != '\n')
            data->map.ord_y++;
    }
    close(fd);
    free(str);
    return (0);
}

int check_map(char *av1, t_data *data)
{
    int i;
    int fd;
    int ret;

    i = 0;
    while (av1[i])
        i++;
    if (av1[i -4] != '.' || av1[i -3] != 'b' || av1[i -2] != 'e' || av1[i -1] != 'r')
        return (-5);
    data->map.ord_x = 0;
    data->map.ord_y = 0;
    ret = 0;
    fd = 0;
    i = check_reactangle(av1, data, ret, fd);
    if (i != 0)
        return (i);
    if (data->collect.count == 0 || data->exit.count == 0 || data->player.count != 1)
        return (-2);
    i = parse_map(av1, data);
    if (i != 0)
        return (i);
    return (0);
}