#include "../include/so_long.h"

/**
 * Creates a sprite from an image file.
 * 
 * @param game A pointer to the game structure.
 * @param sprite_path Path to the image file for the sprite.
 * 
 * @return A pointer to the newly created sprite, or NULL if an error occurred.
 */
t_sprite	*create_sprite(t_game *game, char *sprite_path)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite)); // Allocate memory for the sprite
	if (!sprite)
	{
		free(sprite_path); // Free the sprite path if memory allocation fails
		gameover(game); // End the game due to memory allocation failure
		return (NULL);
	}
	sprite->img = mlx_xpm_file_to_image(game->mlx, sprite_path, &sprite->width,
			&sprite->height); // Load the image from the file
	if (!sprite->img)
	{
		ft_printf("Failed to load image: %s\n", sprite_path); // Print error message if image loading fails
		free(sprite); // Free the sprite memory
		free(sprite_path); // Free the sprite path memory
		gameover(game); // End the game due to image loading failure
		return (NULL);
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian); // Get the address of the image data
	return (sprite);
}

/**
 * Creates the map by generating sprites for each map tile and rendering them.
 * 
 * @param game A pointer to the game structure.
 */
void	create_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;
	char		*sprite_path;

	y = -1;
	while (++y < game->map.lines) // Iterate over each line of the map
	{
		x = -1;
		while (++x < game->map.colun) // Iterate over each column of the map
		{
			sprite_path = get_sprite_path(game, game->map.map[y][x].type); // Get the path for the current tile type
			if (!sprite_path)
			{
				gameover(game); // End the game if sprite path allocation fails
			}
			game->map.map[y][x].sprt_path = ft_strdup(sprite_path); // Duplicate the sprite path
			sprite = create_sprite(game, sprite_path); // Create a sprite using the path
			create_world(sprite, game, x, y); // Render the sprite onto the world
			mlx_destroy_image(game->mlx, sprite->img); // Destroy the image to free memory
			free(sprite); // Free the sprite memory
		}
	}
}

/**
 * Gets the file path for the sprite image based on the map character.
 * 
 * @param game A pointer to the game structure.
 * @param c The character representing the tile type.
 * 
 * @return The path to the sprite image.
 */
char	*get_sprite_path(t_game *game, char c)
{
	char	*path;

	path = NULL;
	if (c == '1') // If the tile is a wall
	{
		if (rand() % 2 == 0)
			path = WALL; // Choose between two wall images
		else
			path = WALL2;
	}
	else if (c == '0' || c == 'C' || c == 'E' || c == 'P' || c == 'M') // For other tile types
	{
		if (rand() % 2 == 0)
			path = FLOOR; // Choose between three floor images
		else if (rand() % 3 == 0)
			path = FLOOR2;
		else
			path = FLOOR3;
	}
	if (!path)
	{
		ft_printf("Failed to allocate path for character: %c\n", c); // Print error message if path allocation fails
		gameover(game); // End the game due to path allocation failure
	}
	return (path);
}

/**
 * Draws a sprite onto the game world at a specific position.
 * 
 * @param sprite A pointer to the sprite to be drawn.
 * @param game A pointer to the game structure.
 * @param posx The x-coordinate position in the game world.
 * @param posy The y-coordinate position in the game world.
 */
void	create_character(t_sprite *sprite, t_game *game, int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	trans_color;

	trans_color = 0xFFC0CB; // Define the transparent color
	y = -1;
	while (++y < sprite->height) // Iterate over each pixel row of the sprite
	{
		x = -1;
		while (++x < sprite->width) // Iterate over each pixel column of the sprite
		{
			color = get_color_in_pixel(sprite, x, y); // Get the color of the current pixel
			if (color != trans_color) // If the pixel is not transparent
			{
				put_pixel(game->world, posx + x, posy + y, color); // Draw the pixel in the game world
			}
		}
	}
}

/**
 * Renders a tile at a specific position on the map.
 * 
 * @param game A pointer to the game structure.
 * @param x The x-coordinate position on the map.
 * @param y The y-coordinate position on the map.
 */
void	put_tile(t_game *game, int x, int y)
{
	char		*sprite_path;
	t_sprite	*sprite;

	sprite_path = ft_strdup(game->map.map[y][x].sprt_path); // Duplicate the sprite path for the tile
	if (!sprite_path)
	{
		gameover(game); // End the game if path duplication fails
		return ;
	}
	sprite = create_sprite(game, sprite_path); // Create a sprite using the path
	create_world(sprite, game, x, y); // Render the sprite onto the world
	mlx_destroy_image(game->mlx, sprite->img); // Destroy the image to free memory
	free(sprite_path); // Free the duplicated path memory
	free(sprite); // Free the sprite memory
}
