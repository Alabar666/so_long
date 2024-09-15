/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:35:23 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Reads the map from a file and stores it in the game structure.
 * 
 * @param file The path to the map file.
 * @param game A pointer to the game structure.
 */
void	read_map(char *file, t_game *game)
{
	int		fd;
	char	*map;
	char	*mapfile;

	// Open the map file and check for errors.
	fd = open_map_file(file);
	
	// Get the number of lines in the map file.
	game->map.lines = count_lines(file);
	
	// Read the first line of the map file.
	map = get_next_line(fd);
	if (!map)
		game_error(fd, game);
	
	// Set the number of columns based on the length of the first line.
	game->map.colun = ft_strlen(map) - 1;
	
	// Allocate memory to store the entire map data.
	mapfile = ft_calloc(sizeof(char), 10000);
	if (!mapfile)
	{
		game_error(fd, game);
	}
	mapfile[0] = '\0';
	
	// Concatenate all lines of the map into a single string.
	while (map)
	{
		mapfile = ft_strcat(mapfile, map);
		free(map);
		map = get_next_line(fd);
	}
	
	// Store the map data in the game structure and clean up.
	game->map.map_data = ft_strdup(mapfile);
	free(mapfile);
	close(fd);
}

/**
 * Opens a map file and checks its validity.
 * 
 * @param file The path to the map file.
 * @return The file descriptor if successful, -1 otherwise.
 */
int	open_map_file(const char *file)
{
	int	fd;

	// Open the file for reading.
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening map file %s\n", file);
		return (-1);
	}
	
	// Check if the file has the correct extension.
	if (!check_file_ext(file))
	{
		ft_printf("Error map extension %s\n", file);
		close(fd);
		return (-1);
	}
	
	return (fd);
}

/**
 * Allocates memory for the map structure.
 * 
 * @param game A pointer to the game structure.
 */
void	map_malloc(t_game *game)
{
	int	i;

	i = 0;
	
	// Allocate memory for the map array of pointers to tiles.
	game->map.map = (t_tile **)ft_calloc(game->map.lines + 1, sizeof(t_tile *) * SZ);
	if (!game->map.map)
		game_error(0, game);
	
	// Allocate memory for each row of tiles in the map.
	while (i < game->map.lines)
	{
		game->map.map[i] = (t_tile *)ft_calloc(game->map.colun + 1, sizeof(t_tile *) * SZ);
		if (!game->map.map[i++])
			game_error(0, game);
	}
}

/**
 * Updates the type of a tile in the map.
 * 
 * @param game A pointer to the game structure.
 * @param old_pos The old position of the tile.
 * @param new_pos The new position of the tile.
 * @param type The new type of the tile.
 */
void	update_map_tiles(t_game *game, t_pos old_pos, t_pos new_pos, char type)
{
	int	map_old_x;
	int	map_old_y;
	int	map_new_x;
	int	map_new_y;

	// Convert pixel coordinates to map tile coordinates.
	map_old_x = old_pos.x / SZ;
	map_old_y = old_pos.y / SZ;
	map_new_x = new_pos.x / SZ;
	map_new_y = new_pos.y / SZ;
	
	// Update the type of the tile at the new position.
	if (game->map.map[map_new_y][map_new_x].type == '0')
	{
		game->map.map[map_old_y][map_old_x].type = '0';
		game->map.map[map_new_y][map_new_x].type = type;
	}
}
