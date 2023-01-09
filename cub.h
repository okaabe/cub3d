/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:40:05 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/09 17:08:55 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define SCREEN_HEIGHT	480
# define SCREEN_WIDTH	960
# include	"./libft/libft.h"
# include	<stdbool.h>
# include	<fcntl.h>
# include	<mlx.h>
# include	<stdio.h>
# include	<math.h>
# define TEXTURES "NO SO WE EA F C"
# define POSITION "N S E W"
# define white " \n"

typedef struct s_vector
{
	int	x;
	int	y;
	char orientation;
}	t_vector;	

typedef struct s_map_data
{
	char		*so;
	char		*no;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	t_vector	player_position;
	char		**map;
	int			map_width;
	int			map_height;
}	t_map_data;

// player struct
typedef struct s_player
{
	int x;
	int y;
	// int	radius;
	// int	turnDirection;
	// int walkDirection;
	double rotation_angle;
	// int move_speed;
	double rotation_speed;
} t_player;

// mlx struct
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}				t_data;

// both struct as dependencies for frame generator in mlx_loop_hook
typedef struct s_frame_dependencies
{
	t_player	player;
	t_data		mlxData;
	t_map_data	data;
}	t_frame;

t_map_data	get_map(char *file);
void		frameGenerator(t_frame *frameData);
void		initializeMlx(t_data *mlx_data, t_map_data *map);
int			player_moves(int keycode, t_frame *frameData);

#endif