/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/13 20:34:43 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(char *file, t_game *game)
{
	int		fd;
	char	*map;
	char	*mapfile;

	fd = open_map_file(file);
	game->map.lines = count_lines(file);
	map = get_next_line(fd);
	game->map.colun = ft_strlen(map) - 1;
	mapfile = ft_calloc(sizeof(char), 10000);
	if (!mapfile)
	{
		game_error(fd, &game->map, MAP_ERROR);
	}
	mapfile[0] = '\0';
	while (map)
	{
		mapfile = ft_strcat(mapfile, map);
		free(map);
		map = get_next_line(fd);
	}
	game->map.map_data = ft_strdup(mapfile);
	free(mapfile);
	close(fd);
}

int	open_map_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening map file %s\n", file);
		return (-1);
	}
	if (!check_file_ext(file))
	{
		ft_printf("Error map extension %s\n", file);
		close(fd);
		return (-1);
	}
	return (fd);
}

void	map_malloc(t_map *map)
{
	int	i;

	i = 0;
	map->map = (t_tile **)ft_calloc(map->lines + 1, sizeof(t_tile *) * SZ);
	if (!map->map)
		game_error(0, map, MAP_ERROR);
	while (i < map->lines)
	{
		map->map[i] = (t_tile *)ft_calloc(map->colun + 1, sizeof(t_tile *)
				* SZ);
		if (!map->map[i++])
			game_error(0, map, MAP_ERROR);
	}
}
