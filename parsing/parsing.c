/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:32:59 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/17 20:53:03 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

size_t	get_map_len(t_list *map)
{
	size_t	len;

	len = 0;
	while (map)
	{
		if (len < ft_strlen(map->content))
		{
			len = ft_strlen(map->content);
		}
		map = map->next;
	}
	return (len);
}

void	fill_map(t_list **map, t_map_data *data)
{
	int	i;
	int	len;

	data->map_width = get_map_len(*map);
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_list	*get_line(int fd)
{
	char	*content;

	content = get_next_line(fd);
	if (!content)
		return (NULL);
	return (ft_lstnew(content, 0));
}

t_map_data	get_map(char *file)
{
	int			fd;
	t_list		*map;
	t_list		*new;
	t_map_data	data;

	ft_memset(&data, 0, sizeof(data));
	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0 && printf("failed to open\n"))
		exit(1);
	while (true)
	{
		new = get_line(fd);
		if (!new)
			break ;
		ft_lstadd_back(&map, new);
	}
	get_textures(&map, &data);
	fill_map(&map, &data);
	if (!get_player_postion(&data)
		&& printf("there is no player in map"))
		exit(1);
	check_map_walls(data.map, data);
	return (data);
}
