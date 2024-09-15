/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:16:58 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the battle settings in the game structure.
 */
void	init_battle(t_game *game)
{
	game->battle.btl_img = NULL; // Set battle image to NULL
	game->battle.gatk_path = (CGBLATK); // Path for player attack animation
	game->battle.grun_path = (CGBLRUN); // Path for player running animation
	game->battle.eatk_path = (CENYATK); // Path for enemy attack animation
	game->battle.erun_path = (CENYRUN); // Path for enemy running animation
	game->battle.is_running = 0; // Battle is not running
	game->message_display_duration = 0; // Message display duration set to 0
	game->battle.enemy_type = '\0'; // No enemy type specified
}

/**
 * Creates and displays the battle screen.
 */
void	create_battle_screen(t_game *game)
{
	t_sprite	*resized_combat;

	// Allocate memory for the sprite
	resized_combat = (t_sprite *)malloc(sizeof(t_sprite));
	// Set the width and height of the sprite to match the map dimensions
	resized_combat->width = game->map.width;
	resized_combat->height = game->map.height;
	// Create a new image with the sprite's dimensions
	resized_combat->img = mlx_new_image(game->mlx, resized_combat->width,
			resized_combat->height);
	// Get the data address of the new image
	resized_combat->addr = mlx_get_data_addr(resized_combat->img,
			&resized_combat->bits_per_pixel, &resized_combat->line_length,
			&resized_combat->endian);
	// Resize the battle image to fit the new sprite dimensions
	resize_combat(game, resized_combat);
	// Put the resized image to the window
	mlx_put_image_to_window(game->mlx, game->win, resized_combat->img, 0, 0);
	// Destroy the image and free the sprite memory
	mlx_destroy_image(game->mlx, resized_combat->img);
	free(resized_combat);
}

/**
 * Resizes the battle image to fit the dimensions of the battle screen.
 */
void	resize_combat(t_game *game, t_sprite *resized_combat)
{
	int				x;
	int				y;
	unsigned int	color;
	double			src_x;
	double			src_y;

	y = -1;
	while (++y < resized_combat->height)
	{
		x = -1;
		while (++x < resized_combat->width)
		{
			// Calculate the corresponding source coordinates
			src_x = (double)x * game->battle.btl_img->width
				/ resized_combat->width;
			src_y = (double)y * game->battle.btl_img->height
				/ resized_combat->height;
			// Get the color from the source image
			color = get_color_in_pixel(game->battle.btl_img, (int)src_x,
					(int)src_y);
			// Put the color to the destination image
			put_pixel(resized_combat, x, y, color);
		}
	}
}

/**
 * Closes the battle by freeing resources and resetting relevant game settings.
 */
void	close_battle(t_game *game)
{
	if (game->battle.btl_img)
		destroy_sprite(&game->battle.btl_img, game->mlx); // Destroy the battle image
	game->battle.gatk_path = NULL; // Clear the attack path
	game->battle.grun_path = NULL; // Clear the running path
	game->battle.eatk_path = NULL; // Clear the enemy attack path
	game->battle.erun_path = NULL; // Clear the enemy running path
	game->battle.is_running = 0; // Set battle status to not running
	game->is_paused = 0; // Set the game to not paused
	if (game->battle.btl_img)
	{
		mlx_destroy_image(game->mlx, game->battle.btl_img); // Destroy the image if it exists
		free(game->battle.btl_img); // Free the memory of the image
		game->battle.btl_img = NULL; // Set the image pointer to NULL
	}
}
