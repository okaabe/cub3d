/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:42:46 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/15 09:54:53 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void set_textures(t_frame* frame_data)
{
	int index;

	index = 0;
	frame_data->textures = (t_texture *)malloc(sizeof(t_texture ) * 4);
	while (index <= 3)
	{
	frame_data->textures[index].mlxtexture.img = mlx_xpm_file_to_image(frame_data->mlxData.mlx, frame_data->data.direction[index],
	&frame_data->textures[index].width, &frame_data->textures[index].height);
		frame_data->textures[index].mlxtexture.addr = mlx_get_data_addr(frame_data->textures[index].mlxtexture.img,
						&frame_data->textures[index].mlxtexture.bits_per_pixel, &frame_data->textures[index].mlxtexture.line_length, 
						&frame_data->textures[index].mlxtexture.endian);
			frame_data->textures[index].x_ratio = frame_data->textures[index].width / (double)TILE_SIZE;
		index++;
	}
}

double get_player_direction(char direction)
{
	if (direction == 'N')
		return(NORTH);
	else if (direction == 'E')
		return (EAST);
	else if (direction == 'W')
		return (WEST);
	return (SOUTH);
}
int	main(int argc, char **argv)
{
	t_frame		frameData;

	frameData.data = get_map(argv[1]);
	frameData.player.x = (frameData.data.player_position.x * TILE_SIZE) + 16;
	frameData.player.y = (frameData.data.player_position.y * TILE_SIZE) + 16;
	frameData.player.rotation_angle = get_player_direction(frameData.data.player_position.orientation);
	frameData.Fov = FOV_ANGLE * (M_PI / 180);
	frameData.N_rays = MAP_WIDTH;
	
	printf("%d\n", frameData.data.f);
	// initialize the mlx data 
	initializeMlx(&frameData.mlxData, &frameData.data);
	set_textures(&frameData);
	frameGenerator(&frameData);
	// detect the player moves
	mlx_hook(frameData.mlxData.mlx_win, 2, 0, player_moves, &frameData);
	mlx_put_image_to_window(frameData.mlxData.mlx, frameData.mlxData.mlx_win, frameData.mlxData.img, 0, 0);
	mlx_loop(frameData.mlxData.mlx);
}