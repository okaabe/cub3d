/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:32:59 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/09 14:59:52 by aamoussa         ###   ########.fr       */
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

void get_player_postion(t_data	*data)
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

void 	fill_map(t_list **map, t_data *data)
{
	int	i;
	int len;
	
	data->map_width = get_map_len(*map);
	printf("%d :::\n", data->map_width);
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

void	store_it(t_data *data, t_list **map, char *str)
{
	if (!ft_strncmp(str, "NO", ft_strlen(str)))
		data->no = (*map)->content;
	if (!ft_strncmp(str, "SO", ft_strlen(str)))
		data->so = (*map)->content;
	if (!ft_strncmp(str, "WE", ft_strlen(str)))
		data->we = (*map)->content;
	if (!ft_strncmp(str, "EA", ft_strlen(str)))
		data->ea = (*map)->content;
	if (!ft_strncmp(str, "F", ft_strlen(str)))
		data->f = (*map)->content;
	if (!ft_strncmp(str, "C", ft_strlen(str)))
		data->c = (*map)->content;
}

void	get_textures(t_list **map, t_data *data)
{
	char **text;
	int		i;
	int		j;
	char	*content;

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
	if (!data->ea || !data->so || !data->we || !data->f || !data->no || !data->c)
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

t_data get_map(char *file)
{
	int		fd;
	t_list	*map;
	t_list	*new;
	t_data	data;

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
	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	// check_map_walls(data.map);
}
