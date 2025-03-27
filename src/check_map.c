/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:10:19 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 19:20:56 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int    check_wall(char *line)
{
    if(! *line)
        return (0);
    while (*line != '\n' && *line != '\0')
    {
        if (*line != '1')
            return (0);
        line++;
    }
    return (1);
}

int check_game_components(char *line, int *map_comps)
{
    if (*line != '1')
        return (0);
    line++;
    while (*line != '\n')
    {
        if(*line == 'C')
            map_comps[2]++;
        else if(*line == 'E')
            map_comps[3]++;
        else if(*line == 'P')
            map_comps[4]++;
        else if(*line == '0' || *line == '1')
            map_comps[0]++;
        else
            return (0);
        line++;
    }
    if(*(line -1) != '1')
        return (0);
    return (1);
}

int error_check (int fd, t_list **map, int line_nbr, int *score)
{
    char *line;
    int map_comps[5];

    ft_bzero(map_comps, 5 * sizeof(int));
    line = get_next_line(fd);
    map_comps[0]++;
    if (!line)
        return (0);
    map_comps[1] = check_wall(line);
    ft_lstadd_back(map, ft_lstnew(line));
    while (line != NULL && map_comps[1] && map_comps[0] < (line_nbr -2))
    {
        line = get_next_line(fd);
        map_comps[1] = check_game_components(line,map_comps);
        ft_lstadd_back(map, ft_lstnew(line));
        map_comps[0]++;
    }
    line = get_next_line(fd);
    close(fd);
    if (!map_comps[1] || map_comps[2] || map_comps[3] || \
    map_comps[4] != 1 || !check_wall(line))
        return (0);
    *score = map_comps[2];
    ft_lstadd_back(map, ft_lstnew(line));
    return (1);
}