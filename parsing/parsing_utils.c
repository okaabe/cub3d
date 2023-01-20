/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:20:35 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 13:57:44 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*fill_the_grid(char *str, size_t len)
{
	char	*line;

	line = (char *)malloc(len + 1);
	line[len] = 0;
	ft_strlcpy(line, str, len);
	ft_memset(line + (ft_strlen(str) - 1), ' ', len - (ft_strlen(str) - 1));
	return (line);
}

bool	save_player_positioin(int i, char *c, t_map_data	*data)
{
	if (c)
	{
		data->player_position.y = i;
		data->player_position.x = c - data->map[i];
		data->player_position.orientation = *c;
		data->map[data->player_position.y][data->player_position.x] = '0';
		return (true);
	}
	return (false);
}

bool	get_player_postion(t_map_data	*data)
{
	int		i;
	char	*c;
	char	**position;
	int		j;

	position = ft_split(POSITION, ' ');
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (position[j])
		{
			c = ft_strchr(data->map[i], position[j][0]);
			if (c)
				break ;
			j++;
		}
		if (save_player_positioin(i, c, data))
			break ;
		i++;
	}
	i = 0;
	while (position[i])
		free(position[i++]);
	free(position);
	if (!data->map[i])
		return (false);
	return (true);
}
