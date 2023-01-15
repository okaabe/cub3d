/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:50:24 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/15 04:37:38 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"


void draw_cercl_from_player(t_frame *frameData)
{
	float y_index;
	float x_index;
	float r = 200;
	float theta = 0;
	float		x;
	float		y;
	float		x1;
	float		y2;
	t_player	player;
	int			*colors_in_cercle;

	y_index = MAP_HEIGHT + 550;
	x_index = MAP_WIDTH + 1100;
	player = frameData->player;
	while (r)
	{
		theta = 0;
	while (theta <= 360)
	{
		x = x_index + r * cos((theta * M_PI) / 180.0);
		y = y_index + r * sin((theta * M_PI) / 180.0);
		my_mlx_pixel_put(&frameData->mlxData, x * MINI_MAP_SIZE, y * MINI_MAP_SIZE,  0xcd6155);
		theta += 0.5;
	}
		r -= 1;
	}
}

void draw_cercl(t_frame *frameData, int x_index, int y_index, int r)
{
	// float y_index;
	// float x_index;
	// float r = 200;
	float theta = 0;
	float		x;
	float		y;
	float		x1;
	float		y2;
	t_player	player;
	
	int count = 0;
	// y_index = 189;
	// x_index = 206;
	player = frameData->player;
	while (r)
	{
		theta = 0;
	while (theta <= 360)
	{
		x = x_index + r * cos((theta * M_PI) / 180.0);
		y = y_index + r * sin((theta * M_PI) / 180.0);
		my_mlx_pixel_put(&frameData->mlxData, x * MINI_MAP_SIZE, y * MINI_MAP_SIZE,  0x2c0545);
		theta += 0.5;
		count++;
	}
		r -= 1;
	}
	// printf("count %d\n", count);
}

void draw_minimap(t_frame *frameData,int x, int y, int radius)
{
	draw_cercl(frameData, x , y, radius);
}