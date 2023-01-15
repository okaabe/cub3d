#include "cub.h"

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
// void	get_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
// 		return ;
// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }


// put_pixel in frame
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void updatePlayerPosition(t_frame *frameData, double player_x, double player_y)
{
	int y_index;
	int x_index;
	int r = 5;
	int theta = 0;
	int	x;
	int y;
	
	y_index = player_y;
	x_index = player_x; 
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

// initialize the mlx struct
void initializeMlx(t_data *mlx_data, t_map_data *map)
{
	mlx_data->mlx = mlx_init();
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, MAP_WIDTH,  MAP_HEIGHT, "Hello world!");
	mlx_data->img = mlx_new_image(mlx_data->mlx, MAP_WIDTH, MAP_HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, &mlx_data->bits_per_pixel, &mlx_data->line_length,
						&mlx_data->endian);	
}


bool check_point(int x, int y, int radius, t_frame *framedata)
{
	t_vector_db first;
	t_vector_db sec;
	double		distance;
	first.x = framedata->player.x * MINI_MAP_SIZE;
	first.y = framedata->player.y * MINI_MAP_SIZE;
	sec.x = x;
	sec.y = y;
	distance = calculate_distance(first, sec);
	return (distance < radius);
}

bool check(t_frame *framedata,int x, int y)
{
	if ((x >= 0 && x < framedata->data.map_width) && (y >= 0 && y < framedata->data.map_height))
	{
		return true;
	}
	return false;
}

void playerDirection(t_frame* frameData, double x, double y)
{
	double endX = x + (cos(frameData->player.rotation_angle) * 15);
	double endY = y + (sin(frameData->player.rotation_angle) * 15);
	double deltaX = endX - x;
	double deltaY = endY - y;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	endX = x;
	endY = y;
	while (pixels)
	{
	    my_mlx_pixel_put(&frameData->mlxData, endX, endY, 0xcd6155);
	    endX += deltaX;
	    endY += deltaY;
	    --pixels;
	}
}

void draw2Dmap(t_data *mlxData, t_map_data	*map, t_frame *frameData)
{
	int y_index;
	int x_index;
	float r = 200;
	float theta = 0;
	float		x;
	float		y;
	float		x1;
	float		y2;
	t_player	player;
	t_vector_db	first;
	t_vector_db	sec;
	int distance;

	// printf("test : %d\n", (int)x >= 0);
	// exit(1);
	int count = 0;
	first.x = 206;
	first.y = 189;
	sec.x = 
	y_index = frameData->player.y;
	x_index = frameData->player.x;
	printf("plyer.x %f\n", frameData->player.x);
	printf("plyer.y %f\n", frameData->player.y);
	// player = frameData->player;
	draw_minimap(frameData, 206, 189, 200);
	while (r)
	{
		theta = 0;
		while (theta <= 360)
		{
			x = x_index + r * cos((theta * M_PI) / 180.0);
			y = y_index + r * sin((theta * M_PI) / 180.0);
			x1 = first.x + r * cos((theta * M_PI) / 180.0);
			y2 = first.y + r * sin((theta * M_PI) / 180.0);	
			if (((int)x < MAP_WIDTH && (int)x >= 0) && ((int)y < MAP_HEIGHT && (int)y >= 0))
			{	
				if (check(frameData,x / TILE_SIZE, y /TILE_SIZE) && map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
				{	
					my_mlx_pixel_put(mlxData, x1 * MINI_MAP_SIZE, y2 * MINI_MAP_SIZE, 0x17202a);
				}
				else if (check(frameData,x / TILE_SIZE, y /TILE_SIZE) && map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == ' ')
				{
					my_mlx_pixel_put(mlxData, x1 * MINI_MAP_SIZE, y2 * MINI_MAP_SIZE, 0x2c0545);
				}
				else if (check(frameData,x / TILE_SIZE, y / TILE_SIZE) && map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0')
				{	
					my_mlx_pixel_put(mlxData, x1 * MINI_MAP_SIZE, y2 * MINI_MAP_SIZE, 0xfdfefe);	
				}
				else
				{	
					my_mlx_pixel_put(mlxData, x1 * MINI_MAP_SIZE, y2 * MINI_MAP_SIZE, 0x2c0545);
				}
			}
			theta += 0.4;
			count++;
		}
		r -= 1;
	}
	updatePlayerPosition(frameData, 206, 189);
	playerDirection(frameData, 206 * MINI_MAP_SIZE, 189 * MINI_MAP_SIZE);

}


// void check_facing(t_frame *framData, int ray)
// {
// 	if (framData->rays[ray].is_ray_facing_left)
// 		printf("ray is facing left\n");
// 	if (framData->rays[ray].isray_facing_right)
// 		printf("ray is facing right\n");
// 	if (framData->rays[ray].isray_facing_down)
// 		printf("ray is facing down\n");
// 	if (framData->rays[ray].isray_facing_up)
// 		printf("ray is facing up\n");
// }

void get_distance(t_frame *framedata, t_vector_db distances, int ray)
{
	if (distances.x == 0)
	{	
		//printf("i got : %f\n", distances.y);
		framedata->rays[ray].vert_hit = true;
		framedata->rays[ray].hor_hit = false;
		framedata->rays[ray].distance = distances.y;
		return;
	}
	if (distances.y == 0)
	{
		//printf("i got : %f\n", distances.x);	
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

	// if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
	// 	return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}


unsigned int	put_texture(t_frame* frameData, int x_frame, int y_frame, double wall_height)
{
	int x;
	int	y;
	unsigned int color;		
	char *dst;

	 x = x_frame % frameData->test_texture.width;
	y = y_frame % frameData->test_texture.height;

	// if (frameData->rays->hor_hit)
	// {

	// }
	color = get_pixel_color(&frameData->test_texture.mlxtexture, x, y);
	return (color);
}

void drawWall(t_frame *frameData, double wallHeight, double projectionDistance, int x_index, int x_txr)
{
	double y_ratio = frameData->test_texture.height / wallHeight;
	int y_txr;
	int y_index;
	unsigned int color;

	int end = (MAP_HEIGHT / 2)  + (wallHeight / 2);
	y_index = ((MAP_HEIGHT) / 2 ) - (wallHeight / 2);
	int y_index_init = y_index;
	if(y_index < 0)
		y_index = 0;
	if (end > MAP_HEIGHT)
		end = MAP_HEIGHT;
	while (y_index <  end)
	{
		y_txr = y_ratio * (y_index - y_index_init);
		color = put_texture(frameData, x_txr, y_txr, wallHeight);
		my_mlx_pixel_put(&frameData->mlxData, x_index, y_index, color);
		y_index++;
	}	
}

void renderWall(t_frame* frameData)
{
	double x_ratio = frameData->test_texture.width / (double)TILE_SIZE;
	int x_txr;
	double wallHeight;
	double projectionDistance;
	int i;
	double	ray_distance;

	int raynumber = frameData->N_rays;


	i = 0;
	while (i < raynumber)
	{
		x_txr = x_ratio * ((frameData->rays[i].hor_hit) ? ((int)frameData->rays[i].x % TILE_SIZE) : ((int)frameData->rays[i].y % TILE_SIZE));
		ray_distance = frameData->rays[i].distance * cos(frameData->rays[i].ray_angle - frameData->player.rotation_angle);
		projectionDistance = ((MAP_WIDTH) / 2) / tan(frameData->Fov / 2);
		wallHeight = (TILE_SIZE / ray_distance) * projectionDistance;
		drawWall(frameData, wallHeight, projectionDistance, i, x_txr);
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
		//check_facing(frameData, i);
		distances.x = Horz_rays(frameData, i);
		distances.y = vert_rays(frameData, i);
		get_distance(frameData,distances,i);
		drawray(frameData, ray_angle, frameData->rays[i].distance, i);
		ray_angle += frameData->Fov / frameData->N_rays;
		i++;
	}
	return (0);
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
	draw2Dmap(&(frameData->mlxData), &frameData->data, frameData);
	// castingRays(frameData);
	//updatePlayerPosition(frameData, 5);
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