/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:09:47 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/25 12:22:26 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx_Linux/mlx.h"
# include "errno.h"
# include "fcntl.h"
# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"


typedef struct s_win
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
}				t_window;

typedef struct s_img
{
	void		*img;
	int			width;
	int			height;
	int			x;
	int			y;
	int			count;
}				t_img;

typedef struct s_map
{
	char		**map;
	int			ord_x;
	int			ord_y;
	int			start_h;
	int			end_h;
	int			start_w;
	int			end_w;
}				t_map;

typedef struct s_gnl
{
	char		*leftover;
	char		*line;
}				t_gnl;

typedef struct s_data
{
	t_window	window;
	t_map		map;
	t_img		wall;
	t_img		collect;
	t_img		player;
	t_img		exit;
	t_gnl		gnl;
	int			move;

}				t_data;

void			print_map(t_data *data);
void			ft_return(t_data *data, int code);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *str, int start);
int				ft_putnbr(int n);
int				ft_putstr(char *s);
int				handle_close(t_data *data);
int				ft_init(char *av1, t_data *data);
int				check_map(char *av1, t_data *data);
int				handle_key(int keycode, t_data *data);

char			*get_next_line(int fd, int buff, t_data *data);
char			*ft_copy(t_data *data);
char			*ft_strcat(char *s1, char *s2);

#endif
