/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:31:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/18 19:44:58 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_tile	**duplicate_tile_map(t_tile **map, int lines, int colun)
{
	int		i;
	int		j;
	t_tile	**map_dup;

	map_dup = (t_tile **)ft_calloc(lines, sizeof(t_tile *));
	if (!map_dup)
		return (NULL);
	i = -1;
	while (++i < lines)
	{
		map_dup[i] = (t_tile *)ft_calloc(colun, sizeof(t_tile));
		if (!map_dup[i])
		{
			free_tile_map(map_dup, lines);
			return (NULL);
		}
		j = -1;
		while (++j < colun)
			map_dup[i][j].type = map[i][j].type;
	}
	return (map_dup);
}

int	check_map_winability(t_game *game)
{
	t_tile	**map_dup;
	int		collec_found;
	int		exit_found;

	collec_found = 0;
	exit_found = 0;
	map_dup = duplicate_tile_map(game->map.map, game->map.lines,
			game->map.colun);
	if (!map_dup)
	{
		ft_printf("Error\nMemory allocation failed during map duplication\n");
		return (0);
	}
	explore_map(game, map_dup, game->map.start_p1_p.x / SZ,
		game->map.start_p1_p.y / SZ, &collec_found, &exit_found);
	if (collec_found != game->map.goblin || exit_found == 0)
		return (0);
	if (exit_found != 1 || collec_found != game->map.goblin)
		return (0);
	else
		return (1);
}

void	explore_map(t_game *game, t_tile **map, int x, int y, int *collec_found,
		int *exit_found)
{
	char	current_type;

	if (x < 0 || y < 0 || x >= game->map.colun || y >= game->map.lines
		|| map[y][x].type == '1' || map[y][x].type == 'V')
		return ;
	current_type = map[y][x].type;
	map[y][x].type = 'V';
	if (current_type == 'C')
		(*collec_found)++;
	if (current_type == 'E')
		(*exit_found)++;
	explore_map(game, map, x + 1, y, collec_found, exit_found);
	explore_map(game, map, x - 1, y, collec_found, exit_found);
	explore_map(game, map, x, y + 1, collec_found, exit_found);
	explore_map(game, map, x, y - 1, collec_found, exit_found);
}

void	free_tile_map(t_tile **tile_map, int lines)
{
	int i;

	if (!tile_map)
	{
		ft_printf("Warning: Attempting to free a NULL tile map.\n");
		return ;
	}
	i = -1;
	while(++i < lines)
	{
		if (tile_map[i])
		{
			free(tile_map[i]);
			tile_map[i] = NULL;
		}
	}
	free(tile_map);
}
