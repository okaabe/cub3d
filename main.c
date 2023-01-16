/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:42:46 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/16 02:16:02 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_textures(t_frame	*frame_data)
{
	int	index;

	index = 0;
	frame_data->textures = (t_texture *)malloc(sizeof(t_texture) * 4);
	while (index <= 3)
	{
		frame_data->textures[index].mlxtexture.img
			= mlx_xpm_file_to_image(frame_data->mlxdata.mlx,
				frame_data->data.direction[index],
				&frame_data->textures[index].width,
				&frame_data->textures[index].height);
		frame_data->textures[index].mlxtexture.addr
			= mlx_get_data_addr(frame_data->textures[index].mlxtexture.img,
				&frame_data->textures[index].mlxtexture.bits_per_pixel,
				&frame_data->textures[index].mlxtexture.line_length,
				&frame_data->textures[index].mlxtexture.endian);
			frame_data->textures[index].x_ratio
			= frame_data->textures[index].width / (double)TILE_SIZE;
		index++;
	}
}

double	get_player_direction(char direction)
{
	if (direction == 'N')
		return (NORTH);
	else if (direction == 'E')
		return (EAST);
	else if (direction == 'W')
		return (WEST);
	return (SOUTH);
}

int	main(int argc, char **argv)
{
	t_frame	framedata;

	(void)argc;
	framedata.data = get_map(argv[1]);
	framedata.player.x = (framedata.data.player_position.x * TILE_SIZE) + 16;
	framedata.player.y = (framedata.data.player_position.y * TILE_SIZE) + 16;
	framedata.player.rotation_angle
		= get_player_direction(framedata.data.player_position.orientation);
	framedata.Fov = FOV_ANGLE * (M_PI / 180);
	framedata.N_rays = MAP_WIDTH;
	initializemlx(&framedata.mlxdata);
	set_textures(&framedata);
	framegenerator(&framedata);
	mlx_hook(framedata.mlxdata.mlx_win, 2, 0, player_moves, &framedata);
	mlx_put_image_to_window(framedata.mlxdata.mlx,
		framedata.mlxdata.mlx_win, framedata.mlxdata.img, 0, 0);
	mlx_loop(framedata.mlxdata.mlx);
}
