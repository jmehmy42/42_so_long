/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:50:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 22:08:03 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int ft_strlen(char *str, int start)
{
    int i;
    i = start;
    while (str[i])
        i++;
    return (i -  start);
}

char *ft_copy(t_data *data)
{
    char *str;
    int i;

    i = 0;
    str = ft_calloc(ft_strlen(data->gnl.leftover, 0) + 1, 1);
    if (!str)
        return (NULL);
    while (data->gnl.leftover[i])
    {
        str[i] = data->gnl.leftover[i];
        i++;
    }
    free(data->gnl.leftover);
    data->gnl.leftover = NULL;
    return (str);
}

void *ft_calloce1(size_t size, size_t mem)
{
    char *str;
    size_t i;
    str = malloc(size * mem);
    if (!str)
        return (NULL);
    i = 0;
    while (i < size * mem)
    {
        str[i] = 0;
        i++;
    }
    return (str);
}

char *ft_strcat(char *s1, char *s2)
{
    int i;
    int j;
    char *str;
    if(!s1 && !s2)
        return (NULL);
    str = ft_calloc(ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1, 1);
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    } 
    j = 0;
    while (s2[j])
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    free(s1);
    free(s2);
    return (str);
    
}

int ft_strcmp (char *s1, char *s2)
{
    int i;

    i = 0;
    while ((s1[i] || s2[i] ) && s1[i] == s2[i])
        i++;
    if (s1[i] > s2[i] || s1[i] < s2[i])
        return (1);
    else
        return (0);
}