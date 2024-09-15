/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:14:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:34:55 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the game map by loading the map file, setting up the game window, 
 * and performing map checks.
 * 
 * @param file The path to the map file.
 * @param game A pointer to the game structure.
 */
void	map_start(char *file, t_game *game)
{
	init_map(game); // Initialize the map structure.
	read_map(file, game); // Read the map data from the file.
	
	// Calculate the width and height of the map based on tile size (SZ).
	game->map.width = game->map.colun * SZ;
	game->map.height = game->map.lines * SZ;
	
	map_malloc(game); // Allocate memory for the map.
	fill_map(game); // Fill the map with appropriate data.

	// Initialize the mlx (MiniLibX) library.
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		gameover(game); // Handle the error and exit the game.
	}
	
	// Create a new window with the dimensions of the map.
	game->win = mlx_new_window(game->mlx, game->map.width, game->map.height,
			"The Slayer");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		gameover(game); // Handle the error and exit the game.
	}

	// Perform various map checks to ensure validity.
	map_checks(game);
}

/**
 * Initializes the map structure with default values.
 * 
 * @param game A pointer to the game structure.
 */
void	init_map(t_game *game)
{
	// Set all map-related fields to their default values.
	game->map.map = NULL;
	game->map.map_data = NULL;
	game->map.colun = 0;
	game->map.lines = 0;
	game->map.width = 0;
	game->map.height = 0;
	game->map.exit = 0;
	game->map.enemy = 0;
	game->map.goblin = 0;
	game->map.player = 0;
	game->map.start_p1_p = (t_pos){0, 0};
}

/**
 * Counts the number of lines in a map file.
 * 
 * @param file The path to the map file.
 * @return The number of lines in the map file.
 */
int	count_lines(char *file)
{
	int		count;
	char	*str;
	int		fd;

	count = 0;
	
	// Open the file for reading.
	fd = open(file, O_RDONLY);
	
	// Read the file line by line and count the number of lines.
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str); // Free the memory allocated for the line.
		str = get_next_line(fd); // Read the next line.
	}
	
	// Close the file.
	close(fd);
	
	return (count);
}
