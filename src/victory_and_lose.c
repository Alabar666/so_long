#include "../include/so_long.h"

/**
 * Renders the end screen image to the window.
 * 
 * @param game A pointer to the game structure.
 */
void	render_end_screen(t_game *game)
{
	if (game->end_img && game->show_end_screen)
	{
		// Put the end screen image to the window
		mlx_put_image_to_window(game->mlx, game->win, game->end_img->img, 0, 0);
		mlx_do_sync(game->mlx); // Ensure that the image is displayed immediately
	}
}

/**
 * Starts the end game process, displaying the end screen and animating it.
 * 
 * @param game A pointer to the game structure.
 */
void	end_game(t_game *game)
{
	game->show_end_screen = 1; // Set flag to show the end screen
	create_end_screen(game); // Create the initial end screen
	animate_end_screen(game); // Animate the end screen images
}

/**
 * Resizes the end screen image to fit the game's map dimensions.
 * 
 * @param game A pointer to the game structure.
 * @param resized_end The resized end sprite.
 * @param image_path The path to the image to be resized.
 */
void	resize_end(t_game *game, t_sprite *resized_end, char *image_path)
{
	t_sprite		*temp;
	t_pos			pos;
	t_pos			src_pos;
	unsigned int	color;
	t_pos_double	scale;

	// Create a temporary sprite from the image path
	temp = create_sprite(game, image_path);

	// Calculate scale factors based on map and sprite dimensions
	scale.x = (double)game->map.width / resized_end->width;
	scale.y = (double)game->map.height / resized_end->height;

	// Iterate over each pixel in the destination sprite
	pos.y = -1;
	while (++pos.y < game->map.height)
	{
		pos.x = -1;
		while (++pos.x < game->map.width)
		{
			// Calculate source pixel position
			src_pos.x = (int)(pos.x / scale.x);
			src_pos.y = (int)(pos.y / scale.y);

			// Get color from the source sprite and put it in the destination sprite
			color = get_color_in_pixel(temp, src_pos.x, src_pos.y);
			put_pixel(resized_end, pos.x, pos.y, color);
		}
	}

	// Clean up temporary sprite
	mlx_destroy_image(game->mlx, temp->img);
	free(temp);

	// Update dimensions of the resized sprite
	resized_end->width = game->map.width;
	resized_end->height = game->map.height;
}

/**
 * Animates the end screen by cycling through images.
 * 
 * @param game A pointer to the game structure.
 */
void	animate_end_screen(t_game *game)
{
	char	*images[6];
	int		max_frames;
	int		frame;

	max_frames = 6; // Number of frames in the animation
	frame = 0;

	// Initialize the array with image paths
	initialize_end_images(images);

	// Loop through each frame of the animation
	while (frame < max_frames)
	{
		if (game->end_img)
		{
			// Clean up previous end screen image
			mlx_destroy_image(game->mlx, game->end_img->img);
			free(game->end_img);
			game->end_img = NULL;
		}

		// Create and resize the new end screen image
		game->end_img = create_sprite(game, images[frame]);
		resize_end(game, game->end_img, images[frame]);

		// Render the end screen image
		render_end_screen(game);

		// Clean up the end screen image
		if (game->end_img)
			destroy_sprite(&game->end_img, game->mlx);

		usleep(150000); // Pause for 150 milliseconds between frames
		frame++;
	}
}

/**
 * Creates the initial end screen by loading the first image.
 * 
 * @param game A pointer to the game structure.
 */
void	create_end_screen(t_game *game)
{
	char	*images[6];

	// Initialize the array with image paths
	initialize_end_images(images);

	// Clean up any existing end screen image
	if (game->end_img)
	{
		mlx_destroy_image(game->mlx, game->end_img->img);
		free(game->end_img);
		game->end_img = NULL;
	}

	// Create and resize the initial end screen image
	game->end_img = create_sprite(game, images[0]);
	resize_end(game, game->end_img, images[0]);

	// Render the initial end screen image
	render_end_screen(game);
}
