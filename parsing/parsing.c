/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:32:59 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/15 09:54:17 by ahamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


// void	check_map_walls(char **map)
// {
// 	int i;
// 	int j;
// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
			
// 		}
// 	}
	
// }

void get_player_postion(t_map_data	*data)
{
	int i;
	char	*c;
	char	**position;
	int		j;

	position = ft_split(POSITION, ' ');
	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(position[j])
		{
			c = ft_strchr(data->map[i], position[j][0]);
			if (c)
				break;
			j++;
		}
		if (c)
		{
			data->player_position.y = i;
			data->player_position.x = c - data->map[i];
			data->player_position.orientation = *c;
			data->map[data->player_position.y][data->player_position.x] = '0';
			break;
		}
		i++;
	}
}

char *fill_the_grid(char *str,size_t len)
{
	char *line;
	line = (char *)malloc(len + 1);
	line[len] = 0;
	ft_strlcpy(line, str, len);
	ft_memset(line + (ft_strlen(str) - 1), ' ',	len - (ft_strlen(str) - 1));
	return line;
}

size_t get_map_len(t_list *map)
{
	size_t len;

	len = 0;
	while (map)
	{
		if (len < ft_strlen(map->content))
		{
			len = ft_strlen(map->content); 
		}
		map = map->next;
	}
	return len;	
}

void 	fill_map(t_list **map, t_map_data *data)
{
	int	i;
	int len;
	
	data->map_width = get_map_len(*map);
	//data->map_width = 1920 / 32;
	len = ft_lstsize(*map); 
	i = 0;
	data->map = malloc(len * (sizeof(char **) + 1));
	data->map_height = len;
	data->map[len] = NULL;
	while (i < len)
	{
		data->map[i] = fill_the_grid((*map)->content, data->map_width);
		*map = (*map)->next;
		i++;
	}
	
}

bool check_space(char *str)
{
	int i = 0;
	char *test;

	test = " \n";
	while (str[i])
	{
		if (!ft_strchr(test, str[i]))
			return false;
		i++;
	}
	return (true);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


int get_color(char *trgb)
{
	// free
	char **splited_color = ft_split(trgb, ',');

	return (create_trgb(0, ft_atoi(splited_color[0]), ft_atoi(splited_color[1]), ft_atoi(splited_color[2])));
}

void	store_it(t_map_data *data, t_list **map, char *str)
{
	char **splited_path;
	char *txr_path;
	// double free
	splited_path = ft_split((*map)->content, ' ');
	txr_path = ft_substr(splited_path[1], 0, ft_strlen(splited_path[1]) - 1);
	if (!ft_strncmp(str, "NO", ft_strlen(str)))
		data->direction[N] = txr_path;
	if (!ft_strncmp(str, "SO", ft_strlen(str)))
		data->direction[S] = txr_path;
	if (!ft_strncmp(str, "WE", ft_strlen(str)))
		data->direction[W] = txr_path;
	if (!ft_strncmp(str, "EA", ft_strlen(str)))
		data->direction[E] = txr_path;
	if (!ft_strncmp(str, "F", ft_strlen(str)))
		data->f = get_color(splited_path[1]); //data->f = splited_path[1];
	if (!ft_strncmp(str, "C", ft_strlen(str)))
		data->c = get_color(splited_path[1]);
	// free_splited_path
}

void	get_textures(t_list **map, t_map_data *data)
{
	char **text;
	int		i;
	int		j;
	char	*content;

	data->direction = malloc(sizeof(char *) * 4);
	content = NULL;
	i = 0;
	text = ft_split(TEXTURES, ' ');
	while (*map)
	{
		j = 0;
		while(text[j])
		{
			content = ft_strnstr((*map)->content, text[j], ft_strlen((*map)->content));
			if (content)
				break;
			j++;
		}
		if (check_space((*map)->content))
		{
			*map = (*map)->next;		
			continue;
		}
		if	(!text[j])
			break;
		store_it(data, map, text[j]);
		*map = (*map)->next;
	}
	if (!data->direction[0] || !data->direction[1] || !data->direction[2] || !data->f || !data->direction[3] || !data->c)
	{	
		printf("Error : Missing Texture\n");
		exit(1);
	}
}

t_list	*get_line(int fd)
{
	char	*content;
	content = get_next_line(fd);
	if (!content)
		return (NULL);
	return	(ft_lstnew(content, 0));
}

t_map_data get_map(char *file)
{
	int		fd;
	t_list	*map;
	t_list	*new;
	t_map_data	data;

	ft_memset(&data, 0, sizeof(data));
	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{	
		perror("failed to open");
		exit(1);
	}
	while (true)
	{
		new = get_line(fd);
		if (!new)
			break;
		ft_lstadd_back(&map, new);
	}
	get_textures(&map, &data);
	fill_map(&map, &data);
	get_player_postion(&data);
	return data;
	// check_map_walls(data.map);
}
