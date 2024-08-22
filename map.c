/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/22 21:54:36 by hluiz-ma         ###   ########.fr       */
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
	if(!map)
		game_error(fd, game);		
	game->map.colun = ft_strlen(map) - 1;
	mapfile = ft_calloc(sizeof(char), 10000);
	if (!mapfile)
	{
		game_error(fd, game);
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

void	map_malloc(t_game *game)
{
	int	i;

	i = 0;
	game->map.map = (t_tile **)ft_calloc(game->map.lines + 1, sizeof(t_tile *) * SZ);
	if (!game->map.map)
		game_error(0, game);
	while (i < game->map.lines)
	{
		game->map.map[i] = (t_tile *)ft_calloc(game->map.colun + 1, sizeof(t_tile *)
				* SZ);
		if (!game->map.map[i++])
			game_error(0, game);
	}
}

void	update_map_tiles(t_game *game, t_pos old_pos, t_pos new_pos, char type)
{
	int	map_old_x;
	int	map_old_y;
	int	map_new_x;
	int	map_new_y;

	map_old_x = old_pos.x / SZ;
	map_old_y = old_pos.y / SZ;
	map_new_x = new_pos.x / SZ;
	map_new_y = new_pos.y / SZ;
	if (game->map.map[map_new_y][map_new_x].type == '0')
	{
		game->map.map[map_old_y][map_old_x].type = '0';
		game->map.map[map_new_y][map_new_x].type = type;
	}
}
