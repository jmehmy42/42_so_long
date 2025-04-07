/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:22:14 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/07 17:42:17 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void free_lines(char *line, char *tmp)
{
	free(line);
	free(tmp);
}

int	read_map(t_map *s_map, int fd)
{
	char	*line;
	char	*tmp;

	s_map->map = NULL;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			free(s_map->map);
			return (ft_error("Error empty line in map\n"));
		}
		tmp = s_map->map;
		if (!tmp)
			s_map->map = ft_strdup(line);
		else
			s_map->map = ft_strjoin(tmp, line);
		free_lines(line, tmp);
		if (!s_map->map)
		{
			free(s_map->map);
			return (ft_error("Error: reading map\n"));
		}
	}
	return (0);
}
