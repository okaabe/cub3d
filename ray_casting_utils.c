/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 02:17:47 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/16 02:21:15 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// put_pixel in frame
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// initialize the mlx struct
void	initializemlx(t_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx,
			MAP_WIDTH, MAP_HEIGHT, "Hello world!");
	mlx_data->img = mlx_new_image(mlx_data->mlx, MAP_WIDTH, MAP_HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img,
			&mlx_data->bits_per_pixel, &mlx_data->line_length,
			&mlx_data->endian);
}

void	save_hit(t_frame *framedata, bool first, bool sec, int ray)
{
	framedata->rays[ray].vert_hit = first;
	framedata->rays[ray].hor_hit = sec;
}

void	get_distance(t_frame *framedata, t_vector_db distances, int ray)
{
	if (distances.x == 0)
	{
		save_hit(framedata, true, false, ray);
		framedata->rays[ray].distance = distances.y;
		return ;
	}
	if (distances.y == 0)
	{
		save_hit(framedata, false, true, ray);
		framedata->rays[ray].distance = distances.x;
		return ;
	}
	if (distances.x < distances.y)
	{
		save_hit(framedata, false, true, ray);
		framedata->rays[ray].distance = distances.x;
	}
	else
	{
		save_hit(framedata, true, false, ray);
		framedata->rays[ray].distance = distances.y;
	}
}

double	normalize(double ray_angle)
{
	if (ray_angle < 0)
		ray_angle += (M_PI * 2);
	else if (ray_angle > M_PI * 2)
		ray_angle -= (M_PI * 2);
	return (ray_angle);
}