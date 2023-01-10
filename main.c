/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:42:46 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/10 00:09:15 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_frame		frameData;

	frameData.data = get_map(argv[1]);
	frameData.player.x = (frameData.data.player_position.x * 32) + 16;
	frameData.player.y = (frameData.data.player_position.y * 32) + 16;
	frameData.player.rotation_angle = (M_PI / 2);
	// initialize the mlx data 
	initializeMlx(&frameData.mlxData, &frameData.data);
	// render 2d map and update player position (as well as the player direction not yet)
	frameGenerator(&frameData);
	// detect the player moves
	mlx_hook(frameData.mlxData.mlx_win, 2, 0, player_moves, &frameData);
	mlx_put_image_to_window(frameData.mlxData.mlx, frameData.mlxData.mlx_win, frameData.mlxData.img, 0, 0);
	mlx_loop(frameData.mlxData.mlx);
}