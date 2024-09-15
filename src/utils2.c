#include "../include/so_long.h"

/**
 * Displays a "Game Over" screen with animated text.
 * 
 * The text alternates between two images every second.
 * 
 * @param game A pointer to the game structure.
 */
void	put_dead(t_game *game)
{
	char		*current_dead_text;
	static int	frame_counter; // Keeps track of the number of frames

	// Alternate between two "Game Over" texts
	if ((frame_counter / 60) % 2 == 0)
	{
		current_dead_text = LOSE1; // First text image
	}
	else
	{
		current_dead_text = LOSE2; // Second text image
	}

	// Create the sprite from the current text image
	t_sprite	*temp = create_sprite(game, current_dead_text);
	
	// Resize and display the end text on the world
	resize_end_text(game->world, temp);
	
	// Clean up the sprite
	destroy_sprite(&temp, game->mlx);
	
	// Update frame counter and reset if necessary
	frame_counter++;
	if (frame_counter >= 120)
	{
		frame_counter = 0;
	}
}

/**
 * Resizes and draws the end text sprite onto the destination sprite.
 * 
 * @param dest The destination sprite where the end text will be drawn.
 * @param src The source sprite of the end text.
 */
void	resize_end_text(t_sprite *dest, t_sprite *src)
{
	unsigned int	color;
	double			scale_x;
	double			scale_y;
	t_pos			pos;
	t_pos			src_pos;

	// Calculate scale factors for resizing
	scale_x = (double)src->width / dest->width;
	scale_y = (double)src->height / dest->height;

	pos.y = -1;
	while (++pos.y < dest->height)
	{
		pos.x = -1;
		while (++pos.x < dest->width)
		{
			// Calculate source pixel position
			src_pos.x = (int)(pos.x * scale_x);
			src_pos.y = (int)(pos.y * scale_y);

			// Get color from source sprite
			color = get_color_in_pixel(src, src_pos.x, src_pos.y);

			// Draw the color if it's not the transparent color
			if (color != 0xFFC0CB)
			{
				put_pixel(dest, pos.x, pos.y, color);
			}
		}
	}
}

/**
 * Initializes an array with victory images.
 * 
 * @param images An array of strings to store the paths to victory images.
 */
void	initialize_end_images(char *images[])
{
	images[0] = VICTORY1;
	images[1] = VICTORY2;
	images[2] = VICTORY3;
	images[3] = VICTORY4;
	images[4] = VICTORY5;
	images[5] = VICTORY6;
}
