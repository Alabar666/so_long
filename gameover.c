/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/18 20:22:02 by hluiz-ma         ###   ########.fr       */
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

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}
/*
void	free_map(t_map *map)
{
	int	i;
	int j;

	if(map->map)
	{
		i = -1;
		while(++i < map->lines)
		{
			if(map->map[i])
			{
				j = -1;
				while(++j < map->colun)
				{
					if(map->map[i][j].sprite)
						free(map->map[i][j].sprite);
				}
				free(map->map[i]);
			}
			free(map->map);
		}
	}
	*/