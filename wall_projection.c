/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:00:15 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/21 13:04:39 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

unsigned int	put_texture(t_texture *txr, int x_frame, int y_frame)
{
	unsigned int	color;

	color = get_pixel_color(&txr->mlxtexture, x_frame, y_frame);
	return (color);
}

int	get_x_txr(t_frame *frameData, t_texture *txr, int x_index)
{
	if (frameData->rays[x_index].hor_hit)
		return (txr->x_ratio * ((int)frameData->rays[x_index].x % TILE_SIZE));
	else
		return (txr->x_ratio * ((int)frameData->rays[x_index].y % TILE_SIZE));
}

void	drawall(t_frame *frameData, double wallHeight, int x_index)
{
	int			y_index;
	int			x_txr;
	t_texture	*txr;
	int			end;
	int			y_index_init;

	txr = get_texture(frameData, x_index);
	x_txr = get_x_txr(frameData, txr, x_index);
	end = (MAP_HEIGHT / 2) + (wallHeight / 2);
	y_index = ((MAP_HEIGHT) / 2) - (wallHeight / 2) - 1;
	y_index_init = y_index; 
	if (y_index < 0)
		y_index = 0;
	else
		f_c(frameData, x_index, (MAP_HEIGHT / 2) - (wallHeight / 2));
	if (end > MAP_HEIGHT)
		end = MAP_HEIGHT;
	else
		f_c(frameData, x_index, (MAP_HEIGHT / 2) + (wallHeight / 2));
	while (++y_index < end)
	{
		my_mlx_pixel_put(&frameData->mlxdata, x_index,
			y_index, put_texture(txr, x_txr, 
				(txr->height / wallHeight) * (y_index - y_index_init)));
	}
}

void	renderwall(t_frame *frameData)
{
	double	wallheight;
	double	projectiondistance;
	int		i;
	double	ray_distance;

	i = 0;
	while (i < frameData->n_rays)
	{
		ray_distance = frameData->rays[i].distance
			* cos(frameData->rays[i].ray_angle
				- frameData->player.rotation_angle);
		projectiondistance = ((MAP_WIDTH) / 2) / tan(frameData->fov / 2);
		wallheight = (TILE_SIZE / ray_distance) * projectiondistance;
		drawall(frameData, wallheight, i);
		i++;
	}
}
