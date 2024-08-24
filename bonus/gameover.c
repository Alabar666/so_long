/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 17:18:30 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	game_error(int fd, t_game *game)
{
	if (fd)
		close(fd);
	ft_printf("The map file is not valid.");
	gameover(game);
}

int	gameover(t_game *game)
{
	if (game == NULL)
		return (-1);
	free_map(&game->map);
	if (game->gbl)
	{
		free_all_goblins(game->gbl);
		game->gbl = NULL;
	}
	if (game->eny)
	{
		free_all_enemies(game->eny);
		game->eny = NULL;
	}
	if (game->world)
	{
		if (game->world->img)
		{
			mlx_destroy_image(game->mlx, game->world->img);
			game->world->img = NULL;
		}
		free(game->world);
		game->world = NULL;
	}
	free_mlx(game);
	exit(0);
}

void	free_mlx(t_game *game)
{
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_map(t_map *map)
{
	if (!map)
	{
		ft_printf("Warning: Attempting to free a NULL map.\n");
		return ;
	}
	if (map->map_data)
	{
		free(map->map_data);
		map->map_data = NULL;
	}
	if (map->map)
	{
		free_tile_map(map->map, map->lines, map->colun);
		map->map = NULL;
	}
}

void	destroy_sprite(t_sprite **sprite, void *mlx)
{
	if (*sprite)
	{
		if ((*sprite)->img)
		{
			mlx_destroy_image(mlx, (*sprite)->img);
			(*sprite)->img = NULL;
		}
		free(*sprite);
		*sprite = NULL;
	}
}
