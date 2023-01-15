#include "cub.h"

// put_pixel in frame
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// initialize the mlx struct
void initializeMlx(t_data *mlx_data, t_map_data *map)
{
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, MAP_WIDTH,  MAP_HEIGHT, "Hello world!");
	mlx_data->img = mlx_new_image(mlx_data->mlx, MAP_WIDTH, MAP_HEIGHT);
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
			y_index = (totalY * TILE_SIZE) - 1;
			while (++y_index < ((totalY + 1) * TILE_SIZE))
			{
				x_index = (totalX * TILE_SIZE) - 1;
				while (++x_index < ((totalX + 1) * TILE_SIZE))
				{
					if (map->map[totalY][totalX] == '1')
						my_mlx_pixel_put(mlxData, x_index * MINI_MAP_SIZE , y_index * MINI_MAP_SIZE, 0x17202a);
					else if (map->map[totalY][totalX] == ' ')
						my_mlx_pixel_put(mlxData, x_index * MINI_MAP_SIZE, y_index * MINI_MAP_SIZE, 0x2c0545);	
					else
						my_mlx_pixel_put(mlxData, x_index * MINI_MAP_SIZE , y_index * MINI_MAP_SIZE, 0xfdfefe);
				}
			}
	 	}
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
	printf("player angle = %f\n", frameData->player.rotation_angle); 
	while (r)
	{
		theta = 0;
	while (theta <= 360)
	{
		x = x_index + r * cos((theta * M_PI) / 180.0);
		y = y_index + r * sin((theta * M_PI) / 180.0);
		my_mlx_pixel_put(&frameData->mlxData, x * MINI_MAP_SIZE, y * MINI_MAP_SIZE,  0xcd6155);
		theta++;
	}
	r--;
	}
}

void get_distance(t_frame *framedata, t_vector_db distances, int ray)
{
	if (distances.x == 0)
	{	
		framedata->rays[ray].vert_hit = true;
		framedata->rays[ray].hor_hit = false;
		framedata->rays[ray].distance = distances.y;
		return;
	}
	if (distances.y == 0)
	{
		framedata->rays[ray].hor_hit = true;
		framedata->rays[ray].vert_hit = false;
		framedata->rays[ray].distance = distances.x;
		return;
	}
	if (distances.x < distances.y)
	{
			framedata->rays[ray].vert_hit = false;
			framedata->rays[ray].hor_hit = true;
			framedata->rays[ray].distance = distances.x;	
	}
	else
	{
		framedata->rays[ray].hor_hit = false;	
		framedata->rays[ray].vert_hit = true;
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
unsigned int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}


// void get_texture(t_frame *frameData, int x, int y)
// {
// 	if (frameData->player.rotation_angle >= (M_PI / 4) && frameData->player.rotation_angle < (3 * M_PI) / 4)
// 		return (frameData->textures);
// }

unsigned int	put_texture(t_texture * txr, int x_frame, int y_frame)
{
	unsigned int color;		
	char *dst;

	color = get_pixel_color(&txr->mlxtexture, x_frame, y_frame);
	return (color);
}

t_texture *get_texture(t_frame *frame_data, int i)
{
	if (frame_data->rays[i].ray_angle > 0 && frame_data->rays[i].ray_angle < M_PI && frame_data->rays[i].hor_hit)
		return (&frame_data->textures[S]);
	else if (frame_data->rays[i].ray_angle > M_PI / 2 && frame_data->rays[i].ray_angle < M_PI + (M_PI / 2) && frame_data->rays[i].vert_hit)
		return (&frame_data->textures[W]);
	else if (frame_data->rays[i].ray_angle > M_PI && frame_data->rays[i].ray_angle < 2 * M_PI && frame_data->rays[i].hor_hit)
		return (&frame_data->textures[N]);
	return (&frame_data->textures[E]);
}

void floor_and_ceiling(t_frame* frameData, int x_index, int y)
{
	int color;
	int end;
	int start;

	if (y < MAP_HEIGHT / 2)
	{
		end = y;
		color = frameData->data.c;
		start = 0;
	}
	else
	{
		end = MAP_HEIGHT;
		color = frameData->data.f;
		start = y;
	}
	while (start < end)
	{
		my_mlx_pixel_put(&frameData->mlxData, x_index, start, color);
		start++;
	}
}

void drawWall(t_frame *frameData, double wallHeight, int x_index)
{
	int y_txr;
	int y_index;
	int x_txr;
	t_texture * txr;

	txr = get_texture(frameData,x_index);
	if (frameData->rays[x_index].hor_hit)
		x_txr = txr->x_ratio * ((int)frameData->rays[x_index].x % TILE_SIZE);
	else
		x_txr = txr->x_ratio * ((int)frameData->rays[x_index].y % TILE_SIZE);
	x_txr = x_txr % txr->width;
	int end = (MAP_HEIGHT / 2)  + (wallHeight / 2);
	y_index = ((MAP_HEIGHT) / 2 ) - (wallHeight / 2);
	int y_index_init = y_index;
	if(y_index < 0)
		y_index = 0;
	else
		floor_and_ceiling(frameData, x_index, (MAP_HEIGHT / 2)  - (wallHeight / 2));
	if (end > MAP_HEIGHT)
		end = MAP_HEIGHT;
	else
		floor_and_ceiling(frameData, x_index, (MAP_HEIGHT / 2)  + (wallHeight / 2));
	while (y_index <  end)
	{
		y_txr = (txr->height / wallHeight) * (y_index - y_index_init);
		y_txr = y_txr % txr->height;
		my_mlx_pixel_put(&frameData->mlxData, x_index, y_index, put_texture(txr, x_txr, y_txr));
		y_index++;
	}	
}

void renderWall(t_frame* frameData)
{
	double wallHeight;
	double projectionDistance;
	int i;
	double	ray_distance;

	i = 0;
	while (i < frameData->N_rays)
	{
		ray_distance = frameData->rays[i].distance * cos(frameData->rays[i].ray_angle - frameData->player.rotation_angle);
		projectionDistance = ((MAP_WIDTH) / 2) / tan(frameData->Fov / 2);
		wallHeight = (TILE_SIZE / ray_distance) * projectionDistance;
		drawWall(frameData, wallHeight, i);
		i++;
	}
}

int castingRays(t_frame* frameData)
{
	double ray_angle;
	double rays_numbers;
	int		i;
	t_vector_db	distances;
	
	i = 0;
	rays_numbers = frameData->N_rays;
	ray_angle = frameData->player.rotation_angle - (frameData->Fov / 2);
	frameData->rays = malloc(sizeof(t_rays) * (rays_numbers + 1));
	while (i < rays_numbers)
	{
		frameData->rays[i].ray_angle = normalize(ray_angle);
		find_the_facing_of_ray(frameData, i);
		distances.x = Horz_rays(frameData, i);
		distances.y = vert_rays(frameData, i);
		get_distance(frameData,distances,i);
		drawray(frameData, ray_angle, frameData->rays[i].distance, i);
		ray_angle += frameData->Fov / frameData->N_rays;
		i++;
	}
	return (0);
}

void playerDirection(t_frame* frameData)
{
	double endX = (frameData->player.x) + (cos(frameData->player.rotation_angle) * 50);
	double endY = frameData->player.y + (sin(frameData->player.rotation_angle) * 50);
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
	mlx_destroy_image(frameData->mlxData.mlx, frameData->mlxData.img);
	frameData->mlxData.img = mlx_new_image(frameData->mlxData.mlx, MAP_WIDTH, MAP_HEIGHT);
	frameData->mlxData.addr = mlx_get_data_addr(frameData->mlxData.img, &frameData->mlxData.bits_per_pixel, &frameData->mlxData.line_length,
						&frameData->mlxData.endian);	
	mlx_clear_window(frameData->mlxData.mlx, frameData->mlxData.mlx_win);
	castingRays(frameData);
	renderWall(frameData);
	draw2Dmap(&(frameData->mlxData), &frameData->data);
	castingRays(frameData);
	updatePlayerPosition(frameData);
	// playerDirection(frameData);
	mlx_put_image_to_window(frameData->mlxData.mlx, frameData->mlxData.mlx_win, frameData->mlxData.img, 0, 0);
}

void isThereA_wall(double tmp_x, double tmp_y, t_frame* frameData)
{
    int x = tmp_x / TILE_SIZE;
    int y = tmp_y / TILE_SIZE;
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
