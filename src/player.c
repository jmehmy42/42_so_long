/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:27:00 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/27 19:20:23 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_list *find_player (int *counter, t_list *line)
{
    t_list *current;

    current = line->next;
    while(current->next)
    {
        *counter = 0;
        while (*(char *)(current->content + *counter) != 'P' \
        && *(char *)(current->content +  *counter))
            *counter += 1;
        if (*(char *)(current->content + *counter) == 'P')
            break ;
        line = current;
        current = current->next;
    }
    return (line);
}

char *next_position (int dir, t_list *line, int counter)
{
    char *currdir;
    currdir = (char *)(ft_lstlast(line)->content);
    if (dir == UP)
        currdir = (char *)(line->content + counter);
    else if (dir == LEFT)
        currdir = (char *)(line->content + counter - 1);
    else if (dir == RIGHT)
        currdir = (char *)(line->content + counter + 1);
    else if (dir == DOWN)
        currdir = (char *)(line->next->next->content + counter);
    return (currdir);
}

void    move_player(t_window *mlx, int direction)
{
    t_list *line;
    char *new_pos;
    int counter;

    counter = 0;
    line = find_player(&counter, (*mlx).map);
    new_pos = next_position(direction, line, counter);
    if (*new_pos != '1')
    {
        if (*new_pos == 'C')
            (*mlx).score = (*mlx).score - 1;
        else if (*new_pos == 'E' && (*mlx).score == 0)
            exit_game(mlx);
        else if (*new_pos == 'E')
            return ;
        *new_pos = 'P';
        *(char *)(line->content + counter) = '0';
        (*mlx).count_move = (*mlx).count_move + 1;
    }
    return ;
}