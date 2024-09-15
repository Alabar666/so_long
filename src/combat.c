/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 16:42:52 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


// Starts the battle by pausing the game, setting battle state to running,
// waiting for player input, and selecting the enemy type.
void start_battle(t_game *game, char enemy_type)
{
	// Pause the game and start the battle.
	game->is_paused = 1;
	game->battle.is_running = 1;
	game->wait_input = 1;

	// Set the enemy type for the battle.
	game->battle.enemy_type = enemy_type;

	// Set the battle image based on the enemy type (Combat goblin atack or Combat enemy atack).
	if (enemy_type == 'C')
		game->battle.btl_img = create_sprite(game, CGBLATK);
	else if (enemy_type == 'M')
		game->battle.btl_img = create_sprite(game, CENYATK);
}

// Main loop function that keeps the battle screen active while the battle is running.
int battle_loop_hook(t_game *game)
{
	// If the battle is running, create the battle screen.
	if (game->battle.is_running)
		create_battle_screen(game);
	return (0);
}

// Handles key inputs during battle (e.g., escape, attack, or run).
void battle_keys(int key, t_game *game)
{
	// If ESC is pressed, close the battle and trigger game over.
	if (key == ESC)
	{
		close_battle(game);
		gameover(game);
	}
	// If 'A' or LEFT key is pressed, select the attack option.
	else if (key == KEY_A || key == LEFT)
	{
		// Destroy the current battle image (to update the sprite).
		if (game->battle.btl_img)
			destroy_sprite(&game->battle.btl_img, game->mlx);

		// Set the attack sprite based on the enemy type (Combat goblin atack or Combat enemy atack).
		if (game->battle.enemy_type == 'C')
			game->battle.btl_img = create_sprite(game, CGBLATK);
		else if (game->battle.enemy_type == 'M')
			game->battle.btl_img = create_sprite(game, CENYATK);
		
		// Set run_selected to 0, meaning the player chose to attack.
		game->run_selected = 0;
	}
	// If 'D' or RIGHT key is pressed, select the run option.
	else if (key == KEY_D || key == RIGHT)
	{
		// Destroy the current battle image (to update the sprite).
		if (game->battle.btl_img)
			destroy_sprite(&game->battle.btl_img, game->mlx);

		// Set the run sprite based on the enemy type (Combat goblin run or Combat enemy run).
		if (game->battle.enemy_type == 'C')
			game->battle.btl_img = create_sprite(game, CGBLRUN);
		else if (game->battle.enemy_type == 'M')
			game->battle.btl_img = create_sprite(game, CENYRUN);

		// Set run_selected to 1, meaning the player chose to run.
		game->run_selected = 1;
	}
}

