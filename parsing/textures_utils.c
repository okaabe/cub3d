/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 19:03:14 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/21 16:57:22 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_free_splited(char **splited_path)
{
	int	i;

	i = 0;
	while (splited_path[i])
		free(splited_path[i++]);
	free(splited_path);
}

void	ft_clean_content(char ***splited_path, char **txr_path,
		t_list **map, char *str)
{
	int	i;

	i = 0;
	*splited_path = ft_split((*map)->content, ' ');
	while ((*splited_path)[i])
		i++;
	if (i != 2)
	{
		printf("missing textures");
		exit(1);
	}
	*txr_path = ft_substr((*splited_path)[1], 0,
			ft_strlen((*splited_path)[1]) - 1);
	if (ft_strncmp((*splited_path)[0], str, ft_strlen((*splited_path)[0])))
	{
		printf("invalid identifier\n");
		exit(1);
	}
}

void	check_textures(t_map_data *data)
{
	if (!data->direction[0] || !data->direction[1] || !data->direction[2]
		|| !data->f || !data->direction[3] || !data->c)
	{	
		printf("Error : Missing Texture1\n");
		exit(1);
	}
}

void	ft_check_first_line(char **map, t_map_data data)
{
	if (ft_strchr(map[0], '0') || ft_strchr(map[data.map_height - 1], '0'))
	{
		printf("map is not surrounded by walls\n");
		exit(1);
	}
}

int	ft_check_file(char *file)
{
	int		len_path;

	len_path = ft_strlen(file);
	if (len_path < 5)
	{
		printf("invalid file");
		exit(1);
	}
	if (ft_strncmp(".cub", &file[len_path - 4], 3)
		|| !ft_strncmp(".cub", file, 3))
	{
		printf("invalid file");
		exit(1);
	}
	return (0);
}
