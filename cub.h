/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:40:05 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/16 02:56:48 by aamoussa         ###   ########.fr       */
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
# define RAY_WIDTH 20
# define MINI_MAP_SIZE 0.5
# define MAP_WIDTH 1366
# define MAP_HEIGHT 768
# define TILE_SIZE 32
# define NORTH 0
# define EAST (M_PI / 2)
# define SOUTH M_PI
# define WEST (M_PI + (M_PI / 2))
# define N 3
# define E 1
# define S 2
# define W 0

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
	// char		*so;
	// char		*no;
	// char		*we;
	// char		*ea;
	char **direction;
	int			f;
	int			c;
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
	double x;
	double y;
	double	ray_angle;
	double	distance;
	bool	isray_facing_down;
	bool	isray_facing_up;
	bool	isray_facing_right;
	bool	is_ray_facing_left;
	bool	vert_hit;
	bool	hor_hit;
	
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
typedef struct s_textures
{
	int	width;
	int height;
	double x_ratio;
	t_data mlxtexture;
} t_texture;

typedef struct s_frame_dependencies
{
	t_player	player;
	t_data		mlxdata;
	t_map_data	data;
	double		Fov;
	t_texture	*textures;
	double		N_rays;	
	t_rays 		*rays;
}	t_frame;


t_map_data	get_map(char *file);
void		framegenerator(t_frame *frameData);
void		initializemlx(t_data *mlx_data);
int			player_moves(int keycode, t_frame *frameData);
void		find_the_facing_of_ray(t_frame *frameData, int ray);
void		isthere_wall(double tmp_x, double tmp_y, t_frame* frameData);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
double		horz_rays(t_frame *frameData, int ray);
double		vert_rays(t_frame *frameData, int ray);
double		calculate_distance(t_vector_db first, t_vector_db sec);
bool		is_wall(double tmp_x, double tmp_y, t_frame* frameData);
void		drawray(t_frame *frameData, double ray_angle, double distance, int i);
void		draw_minimap(t_frame *frameData,int x, int y, int radius);
void		draw_map(t_map_data	*map, t_frame *frameData);
void		renderWall(t_frame *frameData);
t_texture	*get_texture(t_frame *frame_data, int i);
void		floor_and_ceiling(t_frame *frameData, int x_index, int y);
void		update_player_position(t_frame *framedata, double p_x, double p_y);
void		playerdirection(t_frame	*framedata, double x, double y);
bool		check(t_frame *framedata, int x, int y);
void		get_distance(t_frame *framedata, t_vector_db distances, int ray);
double		normalize(double ray_angle);
bool		verify(t_frame *framedata, t_vector_db horz_touch);
void		floor_and_ceiling(t_frame	*frameData, int x_index, int y);

#endif