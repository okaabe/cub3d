/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 02:17:09 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/21 17:32:16 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	castingrays(t_frame *frameData)
{
	double		ray_angle;
	double		rays_numbers;
	int			i;
	t_vector_db	distances;

	i = 0;
	rays_numbers = frameData->n_rays;
	ray_angle = frameData->player.rotation_angle - (frameData->fov / 2);
	frameData->rays = malloc(sizeof(t_rays) * (rays_numbers + 1));
	while (i < rays_numbers)
	{
		frameData->rays[i].ray_angle = normalize(ray_angle);
		find_the_facing_of_ray(frameData, i);
		distances.x = horz_rays(frameData, i);
		distances.y = vert_rays(frameData, i);
		get_distance(frameData, distances, i);
		drawray(frameData, ray_angle, frameData->rays[i].distance, i);
		ray_angle += frameData->fov / frameData->n_rays;
		i++;
	}
	return (0);
}

void	framegenerator(t_frame *frameData)
{
	mlx_destroy_image(frameData->mlxdata.mlx, frameData->mlxdata.img);
	frameData->mlxdata.img = mlx_new_image(frameData->mlxdata.mlx,
			MAP_WIDTH, MAP_HEIGHT);
	frameData->mlxdata.addr = mlx_get_data_addr(frameData->mlxdata.img,
			&frameData->mlxdata.bits_per_pixel, &frameData->mlxdata.line_length,
			&frameData->mlxdata.endian);
	mlx_clear_window(frameData->mlxdata.mlx, frameData->mlxdata.mlx_win);
	castingrays(frameData);
	renderwall(frameData);
	draw_map(&frameData->data, frameData);
	mlx_put_image_to_window(frameData->mlxdata.mlx,
		frameData->mlxdata.mlx_win, frameData->mlxdata.img, 0, 0);
	free(frameData->rays);
}

void	isthere_wall(double tmp_x, double tmp_y, t_frame *frameData)
{
	t_vector	first_sqr;
	t_vector	sec_sqr;

	first_sqr.x = tmp_x / TILE_SIZE;
	first_sqr.y = frameData->player.y / TILE_SIZE;
	sec_sqr.x = frameData->player.x / TILE_SIZE;
	sec_sqr.y = tmp_y / TILE_SIZE;
	if (frameData->data.map[first_sqr.y][first_sqr.x] != '0')
		return ;
	if (frameData->data.map[sec_sqr.y][sec_sqr.x] != '0')
		return ;
	if (frameData->data.map[(int)(tmp_y / TILE_SIZE)][(int)(tmp_x / TILE_SIZE)]
			== '0')
	{	
		frameData->player.x = tmp_x;
		frameData->player.y = tmp_y;
	}
}

void	valid_move(int keycode, t_frame *frameData)
{
	t_vector_db	tmp;

	tmp.x = frameData->player.x;
	tmp.y = frameData->player.y;
	if (keycode == 13)
	{
		tmp.y += (sin(frameData->player.rotation_angle) * 10);
		tmp.x += (cos(frameData->player.rotation_angle) * 10);
	}
	else if (keycode == 0)
	{
		tmp.y -= (sin(frameData->player.rotation_angle + M_PI / 2) * 10);
		tmp.x -= (cos(frameData->player.rotation_angle + M_PI / 2) * 10);
	}
	else if (keycode == 2)
	{
		tmp.y += (sin(frameData->player.rotation_angle + M_PI / 2) * 10);
		tmp.x += (cos(frameData->player.rotation_angle + M_PI / 2) * 10);
	}
	else if (keycode == 1)
	{
		tmp.y -= (sin(frameData->player.rotation_angle) * 10);
		tmp.x -= (cos(frameData->player.rotation_angle) * 10);
	}
	isthere_wall(tmp.x, tmp.y, frameData);
}

int	player_moves(int keycode, t_frame *frameData)
{
	if (keycode == 53)
		exit_program();
	valid_move(keycode, frameData);
	if (keycode == 123)
		frameData->player.rotation_angle -= (9 * M_PI) / 180;
	else if (keycode == 124)
		frameData->player.rotation_angle += (9 * M_PI) / 180;
	if (frameData->player.rotation_angle < 0)
		frameData->player.rotation_angle += (M_PI * 2);
	else if (frameData->player.rotation_angle > M_PI * 2)
		frameData->player.rotation_angle -= (M_PI * 2);
	framegenerator(frameData);
	return (0);
}
