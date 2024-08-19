/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 20:30:11 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_error(int fd, t_map *map, char *error)
{
	if (fd)
		close(fd);
	if (map)
		free_map(map);
	if (error)
		printf("%s", error);
	else
		printf("Unknown error occurred.\n");
	exit(1);
}

int	gameover(t_game *game)
{
	if (game == NULL)
		return (-1);
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	free_player_sprites(&game->p1);
	free_exit_sprites(&game->ext);
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
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(0);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;
	int j;

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
		i = -1;
		while (++i < map->lines)
		{
			if (map->map[i])
			{
				j = -1;
				while (++j < map->colun) 
				{
					if (map->map[i][j].sprt_path)
					{
						free(map->map[i][j].sprt_path);
						map->map[i][j].sprt_path = NULL;
					}
				}
				free(map->map[i]);
				map->map[i] = NULL;
			}
			else
			{
				ft_printf("Warning: Attempting to free a NULL row.\n");
			}
		}
		free(map->map);
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
		}
		free(*sprite);
		*sprite = NULL;
	}
}
