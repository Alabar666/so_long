/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:50 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 18:20:05 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	map_checks(t_game *game)
{
	t_map	map;

	map = game->map;
	if (map.lines < 3 || map.colun < 3)
		game_error(0, game);
	if (map.goblin == 0 || map.player != 1 || map.exit != 1)
		game_error(0, game);
	if (map_caracter(game) == 0)
		game_error(0, game);
	if (map_max_size_check(game, &game->map) == 0)
		game_error(0, game);
	if (check_wall(game->map) == 0)
		game_error(0, game);
	if (!check_map_winability(game))
		game_error(0, game);
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
	{
		ft_printf("Error: Invalid game->mlx pointer.\n");
		gameover(game);
	}
	if (mlx_get_screen_size(game->mlx, &screen_width, &screen_height) != 0)
	{
		ft_printf("Error\nFailed to get screen size.\n");
		gameover(game);
	}
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

int	map_caracter(t_game *game)
{
	int		i;
	char	current_char;

	i = -1;
	while (game->map.map_data[++i] != '\0')
	{
		current_char = game->map.map_data[i];
		if (current_char != '1' && current_char != '0' && current_char != 'P'
			&& current_char != 'C' && current_char != 'E'
			&& current_char != '\n')
		{
			return (0);
		}
	}
	return (1);
}
