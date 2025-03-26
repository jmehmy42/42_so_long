/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:17:12 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 21:58:38 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char *ft_return1(t_data *data, int mark)
{
    if (mark == -1)
    {
        if (data->gnl.leftover)
            free(data->gnl.leftover);
        if (data->gnl.line)
            free(data->gnl.line);
        return (NULL);
    }
    else
    {
        if (!data->gnl.leftover && mark == -2 && ft_strcmp(data->gnl.line, "") == 0)
        {
            free(data->gnl.line);
            data->gnl.line = NULL;
        }
        return (data->gnl.line);
        
    }
}

char *cut_leftover(t_data *data, int bsn)
{
    int i;
    int j;

    j = ft_strlen(data->gnl.line, bsn);
    if ( j != 0 && bsn != -1)
    {
        data->gnl.leftover = ft_calloc(j, 1);
        if (!data->gnl.leftover)
            return (NULL);
        i = 0;
        bsn++;
        while ( i < j)
        {
            data->gnl.leftover[i] = data->gnl.line[bsn];
            i++;
            bsn++;
        }
        bsn = bsn - i;
        data->gnl.line[bsn] = '\0';
    }
    return (data->gnl.line);
}

int get_str(int fd, char **str, int buff)
{
    int ret;

    *str = ft_calloc(buff + 1, 1);
    if (!*str)
        return (-1);
    ret = read(fd, *str, buff);
    return (ret);
}

int get_line(int fd, t_data *data, int buff)
{
    char *str;
    int mark;
    int i;

    mark = -1;
    i = 0;
    while (mark != 0)
    {
        while (data->gnl.line[i] != '\n' && i < ft_strlen(data->gnl.line, 0))
            i++;
        if (data->gnl.line[i] == '\n')
            mark = 0;
        else
        {
            mark = get_str(fd, &str, buff);
            if (mark == -1)
                return (-1);
            data->gnl.line = ft_strcat(data->gnl.line, str);
            if (mark == 0)
                i = -2;
        }
    }
    return (i);
}

char *get_next_line(int fd, int buff, t_data *data)
{
    int i;

    data->gnl.line = "";
    if (fd < 0 || !buff || read(fd, data->gnl.line, 0) == -1)
        return (NULL);
    data->gnl.line = NULL;
    if (!data->gnl.leftover)
        get_str(fd, &data->gnl.line, buff);
    else
        data->gnl.line = ft_copy(data);
    if (data->gnl.line == NULL)
        return (ft_return1(data, -1));
    i = get_line(fd, data, buff);
    if (i == -1)
        return (ft_return1(data, -1));
    if (i == -2)
        return (ft_return1(data, -2));
    data->gnl.line = cut_leftover(data, i);
    if (data->gnl.line == NULL)
        return (ft_return1(data, -1));
    return (ft_return1(data, 1));
}