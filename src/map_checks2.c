/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:31:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:34:30 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Duplicates the tile map.
 * 
 * @param map The original tile map to be duplicated.
 * @param lines The number of rows in the map.
 * @param colun The number of columns in the map.
 * @return A new duplicated tile map, or NULL if allocation fails.
 */
t_tile	**duplicate_tile_map(t_tile **map, int lines, int colun)
{
	int		i;
	int		j;
	t_tile	**map_dup;

	map_dup = (t_tile **)ft_calloc(lines, sizeof(t_tile *));
	if (!map_dup)
		return (NULL);
	
	// Allocate memory for each row of the duplicated map.
	i = -1;
	while (++i < lines)
	{
		map_dup[i] = (t_tile *)ft_calloc(colun, sizeof(t_tile));
		if (!map_dup[i])
		{
			free_tile_map(map_dup, lines, colun);
			return (NULL);
		}
		
		// Copy the type of each tile from the original map.
		j = -1;
		while (++j < colun)
			map_dup[i][j].type = map[i][j].type;
	}
	return (map_dup);
}

/**
 * Checks if the map is winable by ensuring that all non-wall tiles are reachable.
 * 
 * @param game A pointer to the game structure.
 * @return 1 if the map is winable, 0 otherwise.
 */
int	check_map_winability(t_game *game)
{
	t_tile	**map_dup;
	int		i;
	int		j;

	// Duplicate the tile map to work on.
	map_dup = duplicate_tile_map(game->map.map, game->map.lines,
			game->map.colun);
	if (!map_dup)
		return (0);
	
	// Start exploration from the player’s initial position.
	explore_map(game, map_dup, game->map.start_p1_p.x / SZ,
		game->map.start_p1_p.y / SZ);
	
	// Check if all non-wall tiles are visited.
	i = -1;
	while (++i < game->map.lines)
	{
		j = -1;
		while (++j < game->map.colun)
		{
			if (map_dup[i][j].type != 'V' && map_dup[i][j].type != '1')
				return (free_tile_map(map_dup, game->map.lines,
						game->map.colun), 0);
		}
	}
	free_tile_map(map_dup, game->map.lines, game->map.colun);
	return (1);
}

/**
 * Recursively explores the map to mark reachable tiles.
 * 
 * @param game A pointer to the game structure.
 * @param map The map to be explored.
 * @param x The x-coordinate of the current tile.
 * @param y The y-coordinate of the current tile.
 */
void	explore_map(t_game *game, t_tile **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.colun || y >= game->map.lines
		|| map[y][x].type == '1' || map[y][x].type == 'V')
		return ;
	
	// Mark the current tile as visited.
	map[y][x].type = 'V';
	
	// Recursively explore neighboring tiles.
	explore_map(game, map, x + 1, y);
	explore_map(game, map, x - 1, y);
	explore_map(game, map, x, y + 1);
	explore_map(game, map, x, y - 1);
}

/**
 * Frees the memory allocated for a tile map.
 * 
 * @param tile_map The tile map to be freed.
 * @param lines The number of rows in the map.
 * @param colun The number of columns in the map.
 */
void	free_tile_map(t_tile **tile_map, int lines, int colun)
{
	int	i;
	int	j;

	if (!tile_map)
		return ;
	
	// Free each row of the tile map.
	i = -1;
	while (++i < lines)
	{
		if (tile_map[i])
		{
			j = -1;
			while (++j < colun)
			{
				// Free any allocated sprite paths in the tiles.
				if (tile_map[i][j].sprt_path)
				{
					free(tile_map[i][j].sprt_path);
					tile_map[i][j].sprt_path = NULL;
				}
			}
			free(tile_map[i]);
			tile_map[i] = NULL;
		}
	}
	free(tile_map);
}
