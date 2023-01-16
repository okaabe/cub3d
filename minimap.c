/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:50:24 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/16 01:37:30 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_pixel(t_vector_db	f_cer, t_vector_db	s_cer,
		t_frame	*framedata, t_map_data	*map)
{
	if (((int)f_cer.x < MAP_WIDTH && (int)f_cer.x >= 0)
		&& ((int)f_cer.y < MAP_HEIGHT && (int)f_cer.y >= 0))
	{	
		if (check(framedata, f_cer.x / TILE_SIZE, f_cer.y / TILE_SIZE)
			&& map->map[(int)(f_cer.y / TILE_SIZE)][(int)(f_cer.x / TILE_SIZE)]
				== '1')
			my_mlx_pixel_put(&framedata->mlxdata,
				s_cer.x * MINI_MAP_SIZE, s_cer.y * MINI_MAP_SIZE, 0x17202a);
		else if (check(framedata, f_cer.x / TILE_SIZE, f_cer.y / TILE_SIZE)
			&& map->map[(int)(f_cer.y / TILE_SIZE)][(int)(f_cer.x / TILE_SIZE)]
				== ' ')
			my_mlx_pixel_put(&framedata->mlxdata,
				s_cer.x * MINI_MAP_SIZE, s_cer.y * MINI_MAP_SIZE, 0x2c0545);
		else if (check(framedata, f_cer.x / TILE_SIZE, f_cer.y / TILE_SIZE)
			&& map->map[(int)(f_cer.y / TILE_SIZE)][(int)(f_cer.x / TILE_SIZE)]
			== '0')
			my_mlx_pixel_put(&framedata->mlxdata,
				s_cer.x * MINI_MAP_SIZE, s_cer.y * MINI_MAP_SIZE, 0xfdfefe);
		else
			my_mlx_pixel_put(&framedata->mlxdata,
				s_cer.x * MINI_MAP_SIZE, s_cer.y * MINI_MAP_SIZE, 0x2c0545);
	}
}

void	draw_first_line(t_frame *frameData, t_map_data *map,
	t_vector index, float r)
{
	t_vector_db	f_cer;
	t_vector_db	s_cer;
	float		theta;
	t_vector_db	first;

	theta = 0;
	first.x = 206;
	first.y = 189;
	while (theta <= 360)
	{
		f_cer.x = index.x + r * cos((theta * M_PI) / 180.0);
		f_cer.y = index.y + r * sin((theta * M_PI) / 180.0);
		s_cer.x = first.x + r * cos((theta * M_PI) / 180.0);
		s_cer.y = first.y + r * sin((theta * M_PI) / 180.0);
		draw_pixel(f_cer, s_cer, frameData, map);
		theta += 0.4;
	}
}

void	draw_map(t_map_data	*map, t_frame *frameData)
{
	t_vector	index;
	float		r;
	t_vector_db	first;

	r = 200;
	first.x = 206;
	first.y = 189;
	index.y = frameData->player.y;
	index.x = frameData->player.x;
	draw_minimap(frameData, 206, 189, 200);
	while (r)
	{
		draw_first_line(frameData, map, index, r);
		r -= 1;
	}
	update_player_position(frameData, 206, 189);
	playerdirection(frameData, 206 * MINI_MAP_SIZE, 189 * MINI_MAP_SIZE);
}

void	draw_cercl(t_frame *frameData, int x_index, int y_index, int r)
{
	float		theta;
	float		x;
	float		y;
	t_player	player;

	theta = 0;
	player = frameData->player;
	while (r)
	{
		theta = 0;
		while (theta <= 360)
		{
			x = x_index + r * cos((theta * M_PI) / 180.0);
			y = y_index + r * sin((theta * M_PI) / 180.0);
			my_mlx_pixel_put(&frameData->mlxdata, x * MINI_MAP_SIZE,
				y * MINI_MAP_SIZE, 0x2c0545);
			theta += 0.5;
		}
		r -= 1;
	}
}

void	draw_minimap(t_frame *frameData, int x_index, int y_index, int r)
{
	float		theta;
	float		x;
	float		y;
	t_player	player;

	theta = 0;
	player = frameData->player;
	while (r)
	{
		theta = 0;
		while (theta <= 360)
		{
			x = x_index + r * cos((theta * M_PI) / 180.0);
			y = y_index + r * sin((theta * M_PI) / 180.0);
			my_mlx_pixel_put(&frameData->mlxdata, x * MINI_MAP_SIZE,
				y * MINI_MAP_SIZE, 0x2c0545);
			theta += 0.5;
		}
		r -= 1;
	}
}
