/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:14:56 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:36:03 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Creates a new tile with the specified type and position.
 * 
 * @param type The type of the tile ('P', 'E', 'C', 'M', etc.).
 * @param x The x-coordinate of the tile in pixels.
 * @param y The y-coordinate of the tile in pixels.
 * @return The created tile.
 */
t_tile	new_tile(char type, int x, int y)
{
	t_tile	tile;

	tile.type = type;
	tile.pos.x = x;
	tile.pos.y = y;
	return (tile);
}

/**
 * Fills the map with tiles based on the map data from the game structure.
 * 
 * @param game A pointer to the game structure.
 */
void	fill_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	char	*mapd;

	mapd = game->map.map_data;
	y = 0;
	i = 0;
	
	// Iterate through each character in the map data.
	while (mapd[i] && mapd[i] != '\n')
	{
		x = 0;
		while (mapd[i] && mapd[i] != '\n')
		{
			// Check the type of the current character and update the game state.
			check_type(game, mapd[i], x, y);
			
			// Create a new tile with the specified type and position.
			game->map.map[y][x] = new_tile(mapd[i], x * SZ, y * SZ);
			game->map.map[y][x].sprt_path = NULL;
			x++;
			i++;
		}
		if (mapd[i] == '\n')
			i++;
		y++;
	}
}

/**
 * Checks the type of a character and updates the game state accordingly.
 * 
 * @param game A pointer to the game structure.
 * @param type The character type ('P', 'E', 'C', 'M', etc.).
 * @param x The x-coordinate of the tile in pixels.
 * @param y The y-coordinate of the tile in pixels.
 */
void	check_type(t_game *game, char type, int x, int y)
{
	if (type == 'P')
	{
		game->map.player++;
		game->map.start_p1_p.x = x * SZ;
		game->map.start_p1_p.y = y * SZ;
	}
	else if (type == 'E')
	{
		init_exit(game);
		game->map.exit++;
		game->ext.ex_p.x = x * SZ;
		game->ext.ex_p.y = y * SZ;
	}
	else if (type == 'C')
	{
		game->map.goblin++;
		add_goblin_to_list(game, x * SZ, y * SZ);
	}
	else if (type == 'M')
	{
		game->map.enemy++;
		add_enemy_to_list(game, x * SZ, y * SZ);
	}
}

/**
 * Concatenates two strings and returns the result.
 * 
 * @param dest The destination string.
 * @param src The source string to append to dest.
 * @return The concatenated string.
 */
char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	
	// Move to the end of the destination string.
	while (dest[i])
		i++;
	
	// Append the source string to the destination string.
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * Draws the map on the screen using mlx functions.
 * 
 * @param game A pointer to the game structure.
 */
void	put_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	sprite = NULL;
	y = -1;
	
	// Iterate through each tile in the map.
	while (++y < game->map.lines)
	{
		x = -1;
		while (++x < game->map.colun)
		{
			// Create a sprite for the current tile.
			sprite = create_sprite(game, game->map.map[y][x].sprt_path);
			
			// Draw the sprite on the screen.
			create_world(sprite, game, x, y);
			
			// Clean up the sprite.
			mlx_destroy_image(game->mlx, sprite->img);
			free(sprite);
			sprite = NULL;
		}
	}
}
