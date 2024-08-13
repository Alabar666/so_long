/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/13 21:47:46 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_error(int fd, t_map *map, char *error)
{
	if (fd)
		close(fd);
	if (map)
		free_map(map->map);
	printf("%s", error);
	exit(0);
}

int	gameover(t_game *game)
{
	if (game->map.map)
		free(game->map.map);
	if (game->map.map)
		mlx_destroy_image(game->mlx, game->world->img);
	if (game->world)
		free(game->world);
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (0);
}

void	free_map(t_tile **map)
{
	int	i;

    if (!map)
	{
        return;
	}
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	destroy_sprite(t_sprite **sprite, void *mlx)
{
	if (*sprite)
	{
		if ((*sprite)->img)
		{
			mlx_destroy_image(mlx, (*sprite)->img);
		}
		free(*sprite);
		*sprite = NULL;
	}
}
