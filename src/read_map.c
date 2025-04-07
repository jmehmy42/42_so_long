/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:22:14 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/05 20:14:24 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
/*
static int	reading_loop(t_rmap *s_rmap, int fd)
{
	while (1)
	{
		s_rmap->read_return = read(fd, s_rmap->buffer, BUFFER_SIZE);
		if (s_rmap->read_return == ERROR)
			return (free_mem(s_rmap->buffer, s_rmap->result));
		if (s_rmap->read_return == 0)
			break ;
		if (!s_rmap->result)
		{
			s_rmap->result = ft_strdup(s_rmap->buffer);
			if (!s_rmap->result)
				return (free_mem(s_rmap->buffer, NULL));
		}
		else
		{
			s_rmap->tmp = s_rmap->result;
			s_rmap->result = ft_strjoin(s_rmap->tmp, s_rmap->buffer);
			if (!s_rmap->result)
				return (free_mem(s_rmap->buffer, s_rmap->tmp));
			free(s_rmap->tmp);
		}
		ft_bzero(s_rmap->buffer, BUFFER_SIZE + 1);
	}
	return (0);
}*/

int	read_map(t_map *s_map, int fd)
{
	char *line;
	char *tmp;

	s_map->map = NULL;
	while ((line = get_next_line(fd)))
	{
		if(line[0] == '\n')
		{
			free(line);
			free(s_map->map);
			return (ft_error("Error empty line in map\n"));
		}
		tmp = s_map->map;
		if(!tmp)
			s_map->map = ft_strdup(line);
		else
			s_map->map = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		if (!s_map->map)
		{
			free(s_map->map);
			return (ft_error("Error: reading map\n"));
		}
	}
	return (0);
}
