/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:50 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:34:01 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Performs various checks on the game map to ensure it is valid.
 * 
 * @param game A pointer to the game structure.
 */
void	map_checks(t_game *game)
{
	t_map	map;

	map = game->map;
	
	// Check if the map dimensions are valid (must be at least 3x3).
	if (map.lines < 3 || map.colun < 3)
		game_error(0, game);
	
	// Check if the map has exactly 1 player, 1 exit, and at least 1 goblin.
	if (map.goblin == 0 || map.player != 1 || map.exit != 1)
		game_error(0, game);
	
	// Check if the map contains valid characters.
	if (map_caracter(game) == 0)
		game_error(0, game);
	
	// Check if the map size does not exceed the screen size.
	if (map_max_size_check(game, &game->map) == 0)
		game_error(0, game);
	
	// Check if the map is surrounded by walls.
	if (!check_wall(game->map))
		game_error(0, game);
	
	// Check if the map is winable.
	if (!check_map_winability(game))
		game_error(0, game);
}

/**
 * Checks if the file extension is ".ber".
 * 
 * @param file The filename to check.
 * @return 1 if the extension is ".ber", 0 otherwise.
 */
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

/**
 * Checks if the map size exceeds the screen dimensions.
 * 
 * @param game A pointer to the game structure.
 * @param map A pointer to the map structure.
 * @return 1 if the map size is valid, 0 otherwise.
 */
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
	
	// Get the screen dimensions.
	if (mlx_get_screen_size(game->mlx, &screen_width, &screen_height) != 0)
	{
		ft_printf("Error\nFailed to get screen size.\n");
		gameover(game);
	}
	
	// Check if the map size exceeds the screen dimensions.
	if (map->width > screen_width || map->height > screen_height)
		return (ft_printf("Error\nMap size exceeds screen dimensions.\n"), 0);
	
	return (1);
}

/**
 * Checks if the map is surrounded by walls.
 * 
 * @param map The map structure.
 * @return 1 if the map is properly enclosed by walls, 0 otherwise.
 */
int	check_wall(t_map map)
{
	int	x;
	int	y;

	// Check top and bottom walls.
	x = 0;
	while (x < map.colun)
	{
		if (map.map[0][x].type != '1' || map.map[map.lines - 1][x].type != '1')
			return (0);
		x++;
	}
	
	// Check left and right walls.
	y = 0;
	while (y < map.lines)
	{
		if (map.map[y][0].type != '1' || map.map[y][map.colun - 1].type != '1')
			return (0);
		y++;
	}
	
	return (1);
}

/**
 * Checks if the map contains only valid characters.
 * 
 * @param game A pointer to the game structure.
 * @return 1 if all characters are valid, 0 otherwise.
 */
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
