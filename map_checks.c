/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:50 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/13 20:48:38 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_checks(t_game *game)
{
	t_map	map;

	map = game->map;
	if (map.lines * map.colun < 4 * 4)
		game_error(0, &game->map, MAP_ERROR);
	if (map.goblin == 0 || map.player == 0 || map.exit != 1)
		game_error(0, &game->map, MAP_ERROR);
	if (map_max_size_check(game, &game->map) == 0)
		game_error(0, &game->map, MAP_ERROR);
	if ((int)ft_strlen(map.map_data) != map.colun * map.lines + map.lines)
		game_error(0, &game->map, MAP_ERROR);
	if (check_wall(game->map) == 0)
		game_error(0, &game->map, MAP_ERROR);
	if (!check_map_winability(game))
		game_error(0, &game->map, MAP_ERROR);
}

int	check_file_ext(const char *file)
{
	size_t		len;
	const char	*exten;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	exten = file + (len - 4);
	return (!ft_strncmp(".ber", exten, 4));
}

int	map_max_size_check(t_game *game, t_map *map)
{
	int	screen_width;
	int	screen_height;

	if (game == NULL)
		return (ft_printf("Error: Invalid game pointer.\n"), 0);
	if (map == NULL)
		return (ft_printf("Error: Invalid map pointer.\n"), 0);
	if (game->mlx == NULL)
		return (ft_printf("Error: Invalid game->mlx pointer.\n"), 0);
	if (mlx_get_screen_size(game->mlx, &screen_width, &screen_height) != 0)
		return (ft_printf("Error\nFailed to get screen size.\n"), 0);
	if (map->width > screen_width || map->height > screen_height)
		return (ft_printf("Error\nMap size exceeds screen dimensions.\n"), 0);
	return (1);
}

int	check_wall(t_map map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map.colun)
	{
		if (map.map[0][x].type != '1' || map.map[map.lines - 1][x].type != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < map.lines)
	{
		if (map.map[y][0].type != '1' || map.map[y][map.colun - 1].type != '1')
			return (0);
		y++;
	}
	return (1);
}
