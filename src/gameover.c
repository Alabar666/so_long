/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:30:49 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Handles errors related to the game. Closes the file descriptor and
 * terminates the game if the map file is invalid.
 * 
 * @param fd The file descriptor to close.
 * @param game A pointer to the game structure.
 */
void	game_error(int fd, t_game *game)
{
	if (fd)
		close(fd); // Close the file descriptor if it's open
	ft_printf("The map file is not valid."); // Print error message
	gameover(game); // Clean up and exit the game
}

/**
 * Performs cleanup operations when the game is over. Frees all allocated
 * resources including the map, goblins, enemies, world images, and MLX resources.
 * 
 * @param game A pointer to the game structure.
 * 
 * @return Returns -1 if the game structure is NULL, otherwise returns 0.
 */
int	gameover(t_game *game)
{
	if (game == NULL)
		return (-1); // Return -1 if the game structure is NULL

	free_map(&game->map); // Free the map data
	if (game->gbl)
	{
		free_all_goblins(game->gbl); // Free all goblins
		game->gbl = NULL;
	}
	if (game->eny)
	{
		free_all_enemies(game->eny); // Free all enemies
		game->eny = NULL;
	}
	if (game->world)
	{
		if (game->world->img)
		{
			mlx_destroy_image(game->mlx, game->world->img); // Destroy the world image
			game->world->img = NULL;
		}
		free(game->world); // Free the world structure
		game->world = NULL;
	}
	free_mlx(game); // Free MLX resources
	exit(0); // Exit the program
}

/**
 * Frees MLX resources including the window and display.
 * 
 * @param game A pointer to the game structure.
 */
void	free_mlx(t_game *game)
{
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win); // Clear the window
		mlx_destroy_window(game->mlx, game->win); // Destroy the window
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx); // Destroy the display
		free(game->mlx); // Free the MLX structure
		game->mlx = NULL;
	}
}

/**
 * Frees the map data and the tile map.
 * 
 * @param map A pointer to the map structure.
 */
void	free_map(t_map *map)
{
	if (!map)
	{
		ft_printf("Warning: Attempting to free a NULL map.\n"); // Print a warning if map is NULL
		return ;
	}
	if (map->map_data)
	{
		free(map->map_data); // Free the map data
		map->map_data = NULL;
	}
	if (map->map)
	{
		free_tile_map(map->map, map->lines, map->colun); // Free the tile map
		map->map = NULL;
	}
}

/**
 * Destroys a sprite and frees its resources.
 * 
 * @param sprite A pointer to a pointer to the sprite structure.
 * @param mlx A pointer to the MLX structure.
 */
void	destroy_sprite(t_sprite **sprite, void *mlx)
{
	if (*sprite)
	{
		if ((*sprite)->img)
		{
			mlx_destroy_image(mlx, (*sprite)->img); // Destroy the sprite image
			(*sprite)->img = NULL;
		}
		free(*sprite); // Free the sprite structure
		*sprite = NULL;
	}
}
