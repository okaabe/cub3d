/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:40:05 by aamoussa          #+#    #+#             */
/*   Updated: 2023/01/09 14:53:24 by aamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define SCREEN_HEIGHT	480
# define SCREEN_WIDTH	960
# include	"./libft/libft.h"
# include	<stdbool.h>
# include	<fcntl.h>
# define TEXTURES "NO SO WE EA F C"
# define POSITION "N S E W"
# define white " \n"
typedef struct s_vector
{
	int	x;
	int	y;
	char orientation;
}	t_vector;	

typedef struct s_data
{
	char		*so;
	char		*no;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	t_vector	player_position;
	char		**map;
	int			map_width;
	int			map_height;
}	t_data;

t_data get_map(char *file);

#endif