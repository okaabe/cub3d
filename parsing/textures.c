/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdy <ahamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:14:02 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/20 14:44:08 by ahamdy           ###   ########.fr       */
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
	i = create_trgb(0, ft_atoi(splited_color[0]),
			ft_atoi(splited_color[1]), ft_atoi(splited_color[2]));
	while (splited_color[j])
		free(splited_color[j++]);
	free(splited_color);
	return (i);
}

void	store_it(t_map_data *data, t_list **map, char *str)
{
	char	**splited_path;
	char	*txr_path;

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
	{
		free(txr_path);
		data->f = get_color(splited_path[1]);
	}
	if (!ft_strncmp(str, "C", ft_strlen(str)))
	{	
		free(txr_path);
		data->c = get_color(splited_path[1]);
	}
	int i = 0;
	while (splited_path[i])
		free(splited_path[i++]);
	free(splited_path);
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
	if (!data->direction[0] || !data->direction[1] || !data->direction[2]
		|| !data->f || !data->direction[3] || !data->c)
	{	
		printf("Error : Missing Texture\n");
		exit(1);
	}
	i = 0;
	while (text[i])
		free(text[i++]);
	free(text);
}
