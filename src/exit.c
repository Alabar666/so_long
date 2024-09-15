/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:29 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:29:22 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the exit-related components in the game.
 * Sets default values for exit position, sprites, and balloon animations.
 */
void	init_exit(t_game *game)
{
	game->ext.ex_p.x = 0; // Exit x position
	game->ext.ex_p.y = 0; // Exit y position
	game->ext.ex1 = NULL; // Pointer for the exit sprite
	game->ext.bl = NULL; // Pointer for the balloon sprite
	game->ext.current_sprite = 0; // Current sprite index (not used in this function)
	// Initialize exit sprites for different directions
	game->ext.exit_sprites[0] = (EXIT_FRONT);
	game->ext.exit_sprites[1] = (EXIT_BACK);
	game->ext.exit_sprites[2] = (EXIT_LEFT);
	game->ext.exit_sprites[3] = (EXIT_RIGHT);
	// Initialize balloon sprites for different emotions
	game->ext.exit_ballom[0] = (EXIT_BHELP);
	game->ext.exit_ballom[1] = (EXIT_BCRY);
	game->ext.exit_ballom[2] = (EXIT_BFEAR);
	game->ext.exit_ballom[3] = (EXIT_BSAD);
}

/**
 * Draws the exit and its associated balloon sprite on the screen.
 * The exit sprite changes based on a frame counter to create an animation effect.
 * The balloon sprite appears with certain conditions based on the frame counter.
 */
void	put_exit(t_game *game)
{
	char		*current_exit;
	char		*current_ballom;
	static int	frame_counter;

	// Determine the current exit sprite based on frame_counter
	current_exit = game->ext.exit_sprites[(frame_counter / 120) % 4];
	// Determine if a balloon sprite should be displayed
	if (frame_counter % 180 < 60)
		current_ballom = game->ext.exit_ballom[(frame_counter / 180) % 4];
	else
		current_ballom = NULL;
	// Create and draw the exit sprite
	game->ext.ex1 = create_sprite(game, current_exit);
	create_character(game->ext.ex1, game, game->ext.ex_p.x, game->ext.ex_p.y);
	if (game->ext.ex1)
		destroy_sprite(&game->ext.ex1, game->mlx); // Clean up after drawing

	// If there's a balloon sprite to be shown, create and draw it
	if (current_ballom)
	{
		game->ext.bl = create_sprite(game, current_ballom);
		create_character(game->ext.bl, game, game->ext.ex_p.x, game->ext.ex_p.y - 40);
		if (game->ext.bl)
			destroy_sprite(&game->ext.bl, game->mlx); // Clean up after drawing
	}
	frame_counter++;
	if (frame_counter > 720)
		frame_counter = 0; // Reset frame_counter to loop the animation
}
