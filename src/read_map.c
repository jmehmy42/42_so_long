/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:22:14 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/02 13:40:28 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	reading_loop(t_rmap *s_rmap, int fd)
{
	while (1)
	{
		s_rmap->read_return = read(fd, s_rmap->str, BUFFER_SIZE);
		if (s_rmap->read_return == ERROR)
			return(free_mem(s_rmap->str, s_rmap->map));
		if (s_rmap->read_return == 0)
			break ;
		if (!s_rmap->map)
		{
			s_rmap->map = ft_strdup(s_rmap->str);
			if (!s_rmap->map)
				return (free_mem(s_rmap->str, NULL));
		}
		else if (s_rmap->map)
		{
			s_rmap->copy = s_rmap->map;
			s_rmap->map = ft_strjoin(s_rmap->copy, s_rmap->str);
			if (!s_rmap->map)
				return (free_mem(s_rmap->str, s_rmap->copy));
			free(s_rmap->copy);
		}
		ft_bzero(s_rmap->str, BUFFER_SIZE + 1);
	}
	return (0);
}

char	*read_map(int fd)
{
	t_rmap s_rmap;

	s_rmap.map = NULL;
	s_rmap.str = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!s_rmap.str)
		return (NULL);
	if (reading_loop(&s_rmap, fd) == ERROR)
	{
		free(s_rmap.str);
		return (NULL);
	}
	free(s_rmap.str);
	return (s_rmap.map);
}
