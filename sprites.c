/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:25:58 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/21 20:48:58 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	*create_sprite(t_game *game, char *sprite_path)
{
	t_sprite	*sprite;
	
	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
	{
		free(sprite_path);
		gameover(game);
		return (NULL);
	}
	sprite->img = mlx_xpm_file_to_image(game->mlx, sprite_path, &sprite->width,
			&sprite->height);
	if (!sprite->img)
	{
		ft_printf("Failed to load image: %s\n", sprite_path);
		free(sprite);
		free(sprite_path);
		gameover(game);
		return (NULL);
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	return (sprite);
}

void	create_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;
	char		*sprite_path;

	y = -1;
	while (++y < game->map.lines)
	{
		x = -1;
		while (++x < game->map.colun)
		{
			sprite_path = get_sprite_path(game, game->map.map[y][x].type);
			if (!sprite_path)
			{
				gameover(game);
			}
			game->map.map[y][x].sprt_path = ft_strdup(sprite_path);
			sprite = create_sprite(game, sprite_path);
			create_world(sprite, game, x, y);
			mlx_destroy_image(game->mlx, sprite->img);
			free(sprite);
		}
	}
}

char	*get_sprite_path(t_game *game, char c)
{
	char	*path;

	path = NULL;
	if (c == '1')
	{
		if (rand() % 2 == 0)
			path = WALL;
		else
			path = WALL2;
	}
	else if (c == '0' || c == 'C' || c == 'E' || c == 'P' || c == 'M')
	{
		if (rand() % 2 == 0)
			path = FLOOR;
		else if (rand() % 3 == 0)
			path = FLOOR2;
		else
			path = FLOOR3;
	}
	if (!path)
	{
		ft_printf("Failed to allocate path for character: %c\n", c);
		gameover(game);
	}
	return (path);
}

void	create_character(t_sprite *sprite, t_game *game, int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	trans_color;

	trans_color = 0xFFC0CB;
	y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color)
			{
				put_pixel(game->world, posx + x, posy + y, color);
			}
		}
	}
}

void	put_tile(t_game *game, int x, int y)
{
	char		*sprite_path;
	t_sprite	*sprite;

	sprite_path = ft_strdup(game->map.map[y][x].sprt_path);
	if (!sprite_path)
	{
		gameover(game);
		return;
	}
	sprite = create_sprite(game, sprite_path);
	create_world(sprite, game, x, y);
	mlx_destroy_image(game->mlx, sprite->img);
	free(sprite_path);
	free(sprite);
}
