# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamoussa <aamoussa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 17:04:41 by ahamdy            #+#    #+#              #
#    Updated: 2023/01/17 20:53:41 by aamoussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c horz_rays.c ray_casting.c vert_rays.c minimap.c wall_projection.c wall_projection_utils.c minimap_utils.c ray_casting_utils.c floor.c \
		parsing/parsing.c parsing/textures.c parsing/parsing_utils.c parsing/check_map.c

#B_SRCS = main.c horz_rays.c ray_casting.c
NAME = cub3D
LIBFT = libft/libft.a

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(LIBFT)
	rm -rf $(BONUS)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(LIBFT) $(SRCS)   -o cub3D

# $(BONUS) : $(LIBFT) $(B_OBJS)
# 	rm -rf $(NAME)
# 	$(CC) $(CFLAGS) $(BONUS) libft/libft.a -lmlx -framework OpenGL -framework AppKit -o so_long

$(LIBFT):
	make  -C libft/ > /dev/null

clean :
	make clean -C libft/ > /dev/null

fclean : clean
	rm -f $(NAME) $(BONUS) so_long 
	rm -rf libft/libft.a

re : fclean all

.PHONY : all clean fclean bonus re