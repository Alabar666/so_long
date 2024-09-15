#include "../include/so_long.h"

/**
 * Initializes an array of direction vectors.
 * 
 * The array holds the directions for movement: up, down, left, and right.
 * 
 * @param directions A 2D array to store the direction vectors.
 */
void	init_directions(int directions[4][2])
{
	directions[0][0] = 0;  // Up direction x-component
	directions[0][1] = -1; // Up direction y-component
	directions[1][0] = 0;  // Down direction x-component
	directions[1][1] = 1;  // Down direction y-component
	directions[2][0] = -1; // Left direction x-component
	directions[2][1] = 0;  // Left direction y-component
	directions[3][0] = 1;  // Right direction x-component
	directions[3][1] = 0;  // Right direction y-component
}

/**
 * Initializes the game structure to default values.
 * 
 * @param game A pointer to the game structure to be initialized.
 */
void	init_game(t_game *game)
{
	if (game == NULL) // Check if the game pointer is valid
		return ;
	game->mlx = NULL; // Initialize MLX pointer
	game->win = NULL; // Initialize window pointer
	game->world = NULL; // Initialize world pointer
	game->end_img = NULL; // Initialize end image pointer
	game->gbl = NULL; // Initialize goblin list pointer
	game->eny = NULL; // Initialize enemy list pointer
	game->lst_gbl_upt = time(NULL); // Initialize goblin update timestamp
	game->lst_eny_upt = time(NULL); // Initialize enemy update timestamp
	game->lst_exit_upt = time(NULL); // Initialize exit update timestamp
	game->global_timer = 0; // Initialize global timer
	game->sprite_index = 0; // Initialize sprite index
	game->is_paused = 0; // Initialize paused state
	game->wait_input = 0; // Initialize wait input state
	game->run_selected = 0; // Initialize run selected state
	game->show_end_screen = 0; // Initialize end screen visibility
	game->message_display_duration = 0; // Initialize message display duration
}

/**
 * Draws a pixel on a sprite at a specified position with a given color.
 * 
 * @param sprite A pointer to the sprite where the pixel will be drawn.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color to be used for the pixel.
 */
void	put_pixel(t_sprite *sprite, int x, int y, int color)
{
	char	*dst;

	// Check if the coordinates are within the sprite's bounds
	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
	{
		ft_printf("Sprite: %p\n", sprite);
		ft_printf("Error: Attempt to draw outside the image bounds (%d, %d)\n",
			x, y);
		return ;
	}
	dst = sprite->addr + (y * sprite->line_length + x * (sprite->bits_per_pixel
				/ 8)); // Calculate the destination address for the pixel
	*(unsigned int *)dst = color; // Set the color at the calculated address
}

/**
 * Retrieves the color of a pixel from a sprite at a specified position.
 * 
 * @param sprite A pointer to the sprite from which the color will be retrieved.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * 
 * @return The color of the pixel.
 */
unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y)
{
	unsigned int	color;

	// Get the color of the pixel at the specified position
	color = *(unsigned int *)(sprite->addr + (y * sprite->line_length + x
				* (sprite->bits_per_pixel / 8)));
	return (color);
}
