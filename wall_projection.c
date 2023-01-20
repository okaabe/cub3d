/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:00:15 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 10:56:54 by aamoussa         ###   ########.fr       */
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

void	drawWall(t_frame *frameData, double wallHeight, int x_index)
{
	int			y_txr;
	int			y_index;
	int			x_txr;
	t_texture	*txr;
	int			end;
	int			y_index_init;

	txr = get_texture(frameData, x_index);
	if (frameData->rays[x_index].hor_hit)
		x_txr = txr->x_ratio * ((int)frameData->rays[x_index].x % TILE_SIZE);
	else
		x_txr = txr->x_ratio * ((int)frameData->rays[x_index].y % TILE_SIZE);
	x_txr = x_txr % txr->width;
	end = (MAP_HEIGHT / 2) + (wallHeight / 2);
	y_index = ((MAP_HEIGHT) / 2) - (wallHeight / 2);
	y_index_init = y_index;
	if (y_index < 0)
		y_index = 0;
	else
	{	
		floor_and_ceiling(frameData, x_index,
			(MAP_HEIGHT / 2) - (wallHeight / 2));
	}
	if (end > MAP_HEIGHT)
	{	
		end = MAP_HEIGHT;
	}
	else
	{	
		floor_and_ceiling(frameData, x_index,
			(MAP_HEIGHT / 2) + (wallHeight / 2));
	}
	while (y_index < end)
	{
		y_txr = (txr->height / wallHeight) * (y_index - y_index_init);
		y_txr = y_txr % txr->height;
		my_mlx_pixel_put(&frameData->mlxdata, x_index,
			y_index, put_texture(txr, x_txr, y_txr));
		y_index++;
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
		ray_distance = frameData->rays[i].distance * cos(frameData->rays[i].ray_angle - frameData->player.rotation_angle);
		projectiondistance = ((MAP_WIDTH) / 2) / tan(frameData->fov / 2);
		wallheight = (TILE_SIZE / ray_distance) * projectiondistance;
		drawWall(frameData, wallheight, i);
		i++;
	}
}
