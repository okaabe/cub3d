#include "cub.h"


#define window_width 15 * 32


// char map[11][15] = {
//             {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
//             {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
//             {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
//             {'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
//             {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
//             {'1', '0', '0', '0', 'P', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
//             {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
//             {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
//             {'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
//             {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
//             {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
// 	};







// put_pixel in frame
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// initialize the mlx struct
void initializeMlx(t_data *mlx_data, t_map_data *map)
{
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, map->map_width * 32, map->map_height * 32, "Hello world!");
	mlx_data->img = mlx_new_image(mlx_data->mlx, map->map_width * 32, map->map_height * 32);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel, &mlx_data->line_length,
						&mlx_data->endian);	
}


void draw2Dmap(t_data * mlxData, t_map_data	*map)
{
	int totalX = -1;
	int totalY = -1;
	int y_index = 0;
	int x_index = 0;
	
	while (++totalY < map->map_height)
	{
		totalX = -1;
		while (++totalX < map->map_width)
		{
			y_index = (totalY * 32) - 1;
			while (++y_index < ((totalY + 1) * 32))
			{
				x_index = (totalX * 32) - 1;
				while (++x_index < ((totalX + 1) * 32))
				{
					if (map->map[totalY][totalX] == '1')
						my_mlx_pixel_put(mlxData, x_index, y_index, 0x17202a);
					else if (map->map[totalY][totalX] == ' ')
						my_mlx_pixel_put(mlxData, x_index, y_index, 0x2c0545);	
					else if (x_index + 1 == (totalX + 1) * 32 || y_index + 1 == (totalY + 1) * 32)
						my_mlx_pixel_put(mlxData, x_index, y_index, 0x17202a);
					else
						my_mlx_pixel_put(mlxData, x_index, y_index, 0xfdfefe);
				}
			}
	 	}
	}	
}
void drawRay(t_frame* frameData, double ray_angle)
{
	double endX = (frameData->player.x) + (cos(ray_angle) * 30);
	double endY = frameData->player.y + (sin(ray_angle) * 30);
	double deltaX = endX - frameData->player.x;
	double deltaY = endY - frameData->player.y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = frameData->player.x;
	endY = frameData->player.y;
	while (pixels)
	{
	    my_mlx_pixel_put(&frameData->mlxData, endX, endY, 0xcd6155);
	    endX += deltaX;
	    endY += deltaY;
	    --pixels;
	}
}

void updatePlayerPosition(t_frame *frameData)
{
	int y_index;
	int x_index;
	int r = 5;
	int theta = 0;
	int	x;
	int y;
	
	y_index = frameData->player.y;
	x_index = frameData->player.x; 
	while (r)
	{
		theta = 0;
	while (theta <= 360)
	{
		x = x_index + r * cos((theta * M_PI) / 180.0);
		y = y_index + r * sin((theta * M_PI) / 180.0);
		my_mlx_pixel_put(&frameData->mlxData, x, y,  0xcd6155);
		theta++;
	}
	r--;
	}
}

int castingRays(t_frame* frameData)
{
	double ray_angle;
	double rays_numbers;

	rays_numbers = frameData->rays.N_rays;
	printf("%f\n", rays_numbers);
	ray_angle = frameData->player.rotation_angle - (frameData->rays.Fov / 2);
	while (rays_numbers)
	{
		drawRay(frameData, ray_angle);
		ray_angle += frameData->rays.Fov / frameData->rays.N_rays;
		rays_numbers--;
	}
}

void playerDirection(t_frame* frameData)
{
	double endX = (frameData->player.x) + (cos(frameData->player.rotation_angle) * 30);
	double endY = frameData->player.y + (sin(frameData->player.rotation_angle) * 30);
	double deltaX = endX - frameData->player.x;
	double deltaY = endY - frameData->player.y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = frameData->player.x;
	endY = frameData->player.y;
	while (pixels)
	{
	    my_mlx_pixel_put(&frameData->mlxData, endX, endY, 0xcd6155);
	    endX += deltaX;
	    endY += deltaY;
	    --pixels;
	}
}

void frameGenerator(t_frame *frameData)
{
	draw2Dmap(&(frameData->mlxData), &frameData->data);
	updatePlayerPosition(frameData);
	playerDirection(frameData);
	castingRays(frameData);
	mlx_put_image_to_window(frameData->mlxData.mlx, frameData->mlxData.mlx_win, frameData->mlxData.img, 0, 0);
}

void isThereA_wall(double tmp_x, double tmp_y, t_frame* frameData)
{
    int x = tmp_x / 32;
    int y = tmp_y / 32;
    if (frameData->data.map[y][x] == '0' && tmp_x != -1 && tmp_y != -1)
    {
        frameData->player.x = tmp_x;
        frameData->player.y = tmp_y;
    }
}

void valid_move(int keycode, t_frame* frameData)
{
    double tmp_x = frameData->player.x;
    double tmp_y = frameData->player.y;
    if (keycode == 13)
    {
        tmp_y +=  (sin(frameData->player.rotation_angle) * 10);
         tmp_x +=  (cos(frameData->player.rotation_angle) * 10);
    }
    else if ( keycode == 0)
    {
         tmp_y -=  (sin(frameData->player.rotation_angle + M_PI / 2) * 10);
        tmp_x -=  (cos(frameData->player.rotation_angle + M_PI / 2) * 10);
    }
    else if (keycode == 2)
    {
        tmp_y +=  (sin(frameData->player.rotation_angle + M_PI / 2) * 10);
        tmp_x +=  (cos(frameData->player.rotation_angle + M_PI / 2) * 10);    
    }
    else if (keycode == 1)
    {
        tmp_y -=  (sin(frameData->player.rotation_angle) * 10);
        tmp_x -=  (cos(frameData->player.rotation_angle) * 10); 
    }
    isThereA_wall(tmp_x, tmp_y, frameData);
}

int player_moves(int keycode, t_frame *frameData)
{
    valid_move(keycode, frameData);
    if (keycode == 123)
        frameData->player.rotation_angle -= (9 * M_PI) / 180;
    else if (keycode == 124)
        frameData->player.rotation_angle += (9 * M_PI) / 180;
    if (frameData->player.rotation_angle < 0)
        frameData->player.rotation_angle += (M_PI * 2);
    else if (frameData->player.rotation_angle > M_PI * 2)
        frameData->player.rotation_angle -= (M_PI * 2);
    frameGenerator(frameData);
    return (0);
}

// int player_moves(int keycode, t_frame *frameData)
// {
// 	// key 13 == up & 1 = down & 2 = right & 0 = left
// 	if (keycode == 13)
// 		frameData->player.y -= 4;
// 	else if ( keycode == 0)
// 		frameData->player.x -= 4;
// 	else if (keycode == 2)
// 		frameData->player.x += 4;
// 	else if (keycode == 1)
// 		frameData->player.y += 4;
// 	else if (keycode == 123)
// 		frameData->player.rotation_angle -= (8 * M_PI) / 180;
// 	else if (keycode == 124)
// 		frameData->player.rotation_angle += (8 * M_PI) / 180;
// 	frameGenerator(frameData);
// 	return (0);
// }

// int	main(void)
// {
// 	t_frame frameData;
// 	// tmp manual initialization of the player position
// 	frameData.player.x = (7 * 32) + 16;
// 	frameData.player.y = (5 * 32) + 16;
// 	frameData.player.rotation_angle = (M_PI / 2);
// 	// initialize the mlx data 
// 	initializeMlx(&frameData.mlxData);
// 	// render 2d map and update player position (as well as the player direction not yet)
// 	frameGenerator(&frameData);
// 	// detect the player moves
// 	// mlx_hook(frameData.mlxData.mlx_win, 2, 0, player_moves, &frameData);
// 	//mlx_hook(mlx_win, 3, 0, reset_player_position, &player);
// 	// mlx_put_image_to_window(frameData.mlxData.mlx, frameData.mlxData.mlx_win, frameData.mlxData.img, 0, 0);
// 	mlx_loop(frameData.mlxData.mlx);
// }