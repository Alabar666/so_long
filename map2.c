/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:14:56 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/22 22:04:10 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_tile	new_tile(char type, int x, int y)
{
	t_tile	tile;

	tile.type = type;
	tile.pos.x = x;
	tile.pos.y = y;
	return (tile);
}

void	fill_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	char	*mapd;

	mapd = game->map.map_data;
	y = 0;
	i = 0;
	while (mapd[i] && mapd[i] != '\n')
	{
		x = 0;
		while (mapd[i] && mapd[i] != '\n')
		{
			check_type(game, mapd[i], x, y);
			game->map.map[y][x] = new_tile(mapd[i], x * SZ, y * SZ);
			game->map.map[y][x].sprt_path = NULL;
			x++;
			i++;
		}
		if (mapd[i] == '\n')
			i++;
		y++;
	}
}

void	check_type(t_game *game, char type, int x, int y)
{
	if (type == 'P')
	{
		game->map.player++;
		game->map.start_p1_p.x = x * SZ;
		game->map.start_p1_p.y = y * SZ;
	}
	else if (type == 'E')
	{
		init_exit(game);
		game->map.exit++;
		game->ext.ex_p.x = x * SZ;
		game->ext.ex_p.y = y * SZ;
	}
	else if (type == 'C')
	{
		game->map.goblin++;
		add_goblin_to_list(game, x * SZ, y * SZ);
	}
	else if (type == 'M')
	{
		game->map.enemy++;
		add_enemy_to_list(game, x * SZ, y * SZ);
	}
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void	put_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	sprite = NULL;
	y = -1;
	while (++y < game->map.lines)
	{
		x = -1;
		while (++x < game->map.colun)
		{
			sprite = create_sprite(game, game->map.map[y][x].sprt_path);
			create_world(sprite, game, x, y);
			mlx_destroy_image(game->mlx, sprite->img);
			free(sprite);
			sprite = NULL;
		}
	}
}
