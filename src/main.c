/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:18:37 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/26 19:40:13 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int check_rectangular (char *file, int total_lines)
{
    char *line;
    int fd;
    int line_len;
    int current_line;

    current_line = 1;
    fd = open (file, O_RDONLY);
    if (fd <= 0 || fd > FOPEN_MAX)
        return (0);
    line = get_next_line(fd);
    line_len = ft_strlen(line);
    current_line++;
    while (line != NULL)
    {
        line = get_next_line(fd);
        if (current_line == (total_lines -1))
            line_len--;
        if (line != NULL && (size_t)line_len != ft_strlen(line))
            return (0);
        line_len = ft_strlen(line);
        current_line++;
    }
    close(fd);
    free(line);
    return (1);
}

int count_lines_in_file(char *file)
{
    char *line;
    int fd;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd <=0 || fd > FOPEN_MAX);
        return (0);
    line = get_next_line(fd);
    i++;
    while (line != NULL)
    {
        line = get_next_line(fd);
        i++;
    }
    clsoe (fd);
    free(line);
    if (!check_rectangular(file, i))
        return (0);
    return (i);
}


int	main(int ac, char **av)
{
	t_window	mlx;
	int			arr[2];

	if (ac != 2)
		return (0);
	mlx.map = 0;
	arr[1] = count_lines_in_file(av[1]);
	arr[0] = open(av[1], O_RDONLY);
	if (arr[0] <= 0 || arr[0] > FOPEN_MAX)
		return (0);
	if (error_check(arr[0],  &(mlx.map), arr[1], &(mlx.score)) != 1)
	{
		ft_lstclear(&(mlx.map), free);
		ft_printf("Error\n");
		return (0);
	}
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, (ft_strlen(mlx.map->content) - 1) \ 
    * 50, ft_lstsize(mlx.map) * 50, "so_long");
	mlx.count_move = 0;
	create_map(&mlx, mlx.map);
	mlx_key_hook(mlx.mlx_win, handle_key_press, (void *)&mlx);
	mlx_hook(mlx.mlx_win, 17, 1L << 17, exit_game, &mlx);
	mlx_loop_hook(mlx.mlx, show_movecount_in_win, (void *)&mlx);
	mlx_loop(mlx.mlx);
}
