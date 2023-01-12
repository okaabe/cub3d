/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:40:05 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/12 00:29:16 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include	"./libft/libft.h"
# include	<stdbool.h>
# include	<fcntl.h>
# include	<mlx.h>
# include	<stdio.h>
# include	<math.h>
# define TEXTURES "NO SO WE EA F C"
# define POSITION "N S E W"
# define white " \n"
# define FOV_ANGLE 60
# define RAY_WIDTH 5

typedef struct s_vector_db
{
	double x;
	double y;
}	t_vector_db;
	
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
	double x;
	double y;
	// int	radius;
	// int	turnDirection;
	// int walkDirection;
	double rotation_angle;
	// int move_speed;
	double rotation_speed;
} t_player;

typedef struct s_rays
{
	double	ray_angle;
	double	distance;
	t_vector_db	horz_touch;
	t_vector_db	vert_touch;
	bool	isray_facing_down;
	bool	isray_facing_up;
	bool	isray_facing_right;
	bool	is_ray_facing_left;
} t_rays;

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
	double		Fov;
	double		N_rays;	
	t_rays 		*rays;
}	t_frame;

t_map_data	get_map(char *file);
void		frameGenerator(t_frame *frameData);
void		initializeMlx(t_data *mlx_data, t_map_data *map);
int			player_moves(int keycode, t_frame *frameData);
void		find_the_facing_of_ray(t_frame *frameData, int ray);
void		isThereA_wall(double tmp_x, double tmp_y, t_frame* frameData);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
double		Horz_rays(t_frame *frameData, int ray);
double		vert_rays(t_frame *frameData, int ray);
double		calculate_distance(t_vector_db first, t_vector_db sec);
bool		is_wall(double tmp_x, double tmp_y, t_frame* frameData);
void		drawray(t_frame* frameData, double ray_angle, double distance);

#endif