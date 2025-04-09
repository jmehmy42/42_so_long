/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:22:14 by jmehmy            #+#    #+#             */
/*   Updated: 2025/04/09 16:04:40 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	chars_check(t_map *s_map, char *str)
{
	int	i;

	i = 0;
	while (s_map->map[i])
	{
		if (char_finder(str, s_map->map[i]) >= 0)
		{
			if (s_map->map[i] == 'P')
				s_map->start++;
			else if (s_map->map[i] == 'C')
				s_map->items++;
			else if (s_map->map[i] == 'E')
				s_map->exit++;
			else if ((s_map->map[0] == '\n') || (s_map->map[i] == '\n'
					&& (s_map->map[i + 1] == '\n')))
				return (ft_error("Error: Consecutive newlines or at end\n"));
			i++;
		}
		else
			return (ft_error("Error: Character other than 01PCE\n"));
	}
	if (s_map->start != 1 || s_map->items == 0 || s_map->exit != 1)
		return (ft_error("Error: Wrong no. of Player/collectibles/exit\n"));
	return (0);
}

static void	update_map(t_map *s_map, char *tmp, char *line)
{
	if (!tmp)
		s_map->map = ft_strdup(line);
	else
		s_map->map = ft_strjoin(tmp, line);
}

static void	free_empty_line(t_map *s_map, char *line)
{
	free(line);
	free(s_map->map);
}

static void	free_lines(char *line, char *tmp)
{
	free(line);
	free(tmp);
}

int	read_map(t_map *s_map, int fd)
{
	char	*line;
	char	*tmp;

	s_map->map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free_empty_line(s_map, line);
			return (ft_error("Error empty line in map\n"));
		}
		tmp = s_map->map;
		update_map(s_map, tmp, line);
		free_lines(line, tmp);
		if (!s_map->map)
		{
			free(s_map->map);
			return (ft_error("Error: reading map\n"));
		}
		line = get_next_line(fd);
	}
	return (0);
}
