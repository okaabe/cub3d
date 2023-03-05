/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:14:02 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/21 17:01:24 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

bool	check_space(char *str)
{
	int		i;
	char	*test;

	i = 0;
	test = " \n";
	while (str[i])
	{
		if (!ft_strchr(test, str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_color(char *trgb)
{
	char	**splited_color;
	int		i;
	int		j;

	j = 0;
	splited_color = ft_split(trgb, ',');
	check_color(splited_color);
	i = create_trgb(0, check_c(ft_atoi((splited_color[0]))),
			check_c(ft_atoi((splited_color[1]))),
			check_c(ft_atoi((splited_color[2]))));
	while (splited_color[j])
		free(splited_color[j++]);
	free(splited_color);
	return (i);
}

void	store_it(t_map_data *data, t_list **map, char *str)
{
	char	**splited_path;
	char	*txr_path;

	txr_path = NULL;
	splited_path = NULL;
	ft_clean_content(&splited_path, &txr_path, map, str);
	if (!ft_strncmp(str, "NO", ft_strlen(str)))
		data->direction[N] = txr_path;
	if (!ft_strncmp(str, "SO", ft_strlen(str)))
		data->direction[S] = txr_path;
	if (!ft_strncmp(str, "WE", ft_strlen(str)))
		data->direction[W] = txr_path;
	if (!ft_strncmp(str, "EA", ft_strlen(str)))
		data->direction[E] = txr_path;
	if (!ft_strncmp(str, "F", ft_strlen(str)))
	{
		free(txr_path);
		data->f = get_color(splited_path[1]);
	}
	if (!ft_strncmp(str, "C", ft_strlen(str)))
	{
		free(txr_path);
		data->c = get_color(splited_path[1]);
	}
	ft_free_splited(splited_path);
}

int	find_texture(int *j, t_list **map, char **text)
{
	char	*content;
	t_list	*tmp;

	content = NULL;
	while (text[*j])
	{
		content = ft_strnstr((*map)->content, text[*j],
				2);
		if (content)
			break ;
		(*j)++;
	}
	if (check_space((*map)->content))
	{
		tmp = *map;
		*map = (*map)->next;
		free(tmp->content);
		free(tmp);
		return (1);
	}
	if (!text[*j])
		return (0);
	return (3);
}

void	get_textures(t_list **map, t_map_data *data)
{
	char	**text;
	int		i;
	int		j;
	t_list	*tmp;

	data->direction = malloc(sizeof(char *) * 4);
	i = 0;
	text = ft_split(TEXTURES, ' ');
	while (*map)
	{
		j = 0;
		tmp = *map;
		if (find_texture(&j, map, text) == 1)
			continue ;
		else if (find_texture(&j, map, text) == 0)
			break ;
		store_it(data, map, text[j]);
		*map = (*map)->next;
		free(tmp->content);
		free(tmp);
	}
	check_textures(data);
	ft_free_splited(text);
}
