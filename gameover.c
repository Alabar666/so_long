/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/11 19:47:06 by hluiz-ma         ###   ########.fr       */
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
  //  free_map(game->map);
	free(game->map.map);
	mlx_destroy_image(game->mlx, game->world->img);
	free(game->world);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
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

