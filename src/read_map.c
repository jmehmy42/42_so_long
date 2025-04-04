/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:22:14 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/04 20:51:45 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
}

char	*read_map(int fd)
{
	t_rmap	s_rmap;

	s_rmap.result = NULL;
	s_rmap.buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!s_rmap.buffer)
		return (NULL);
	if (reading_loop(&s_rmap, fd) == ERROR)
	{
		free(s_rmap.buffer);
		return (NULL);
	}
	free(s_rmap.buffer);
	return (s_rmap.result);
}
