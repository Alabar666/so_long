/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:18:20 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the enemy list to be empty.
 */
void	init_list_enemy(t_game *game)
{
	game->eny = NULL; // Set the enemy list pointer to NULL
}

/**
 * Adds a new enemy to the game's enemy list at the specified coordinates.
 */
void	add_enemy_to_list(t_game *game, int x, int y)
{
	t_enemy	*nw_enemy;
	t_enemy	*current;

	// Create a new enemy
	nw_enemy = new_enemy();
	if (!nw_enemy)
	{
		printf("Error creating enemy.\n"); // Error message if creation fails
		free_enemys(game->eny); // Free existing enemies
		gameover(game); // End the game
	}
	// Initialize the new enemy
	init_enemy(nw_enemy);
	nw_enemy->eny_p.x = x; // Set enemy's x-coordinate
	nw_enemy->eny_p.y = y; // Set enemy's y-coordinate
	// Add the new enemy to the list
	if (game->eny == NULL)
	{
		game->eny = nw_enemy; // First enemy in the list
	}
	else
	{
		current = game->eny;
		// Traverse to the end of the list
		while (current->next != NULL)
			current = current->next;
		// Append the new enemy to the end
		current->next = nw_enemy;
	}
}

/**
 * Initializes the properties of an enemy.
 */
void	init_enemy(t_enemy *enemy)
{
	int	random_dir;

	// Initialize enemy properties
	enemy->eny_p = (t_pos){0, 0}; // Initial position
	enemy->dest_p = (t_pos){0, 0}; // Destination position
	enemy->eny = NULL; // No image assigned yet
	enemy->is_alive = 1; // Enemy is alive
	enemy->current_sprite = 0; // Start with the first sprite
	enemy->is_moving = 0; // Initially not moving
	enemy->dx = 0; // No change in x position
	enemy->dy = 0; // No change in y position
	enemy->steps_remaining = 0; // No steps remaining
	enemy->step_size = 0; // Step size is zero
	enemy->update_interval = 1000 / 60; // Update interval for animation
	enemy->last_update_time = clock(); // Initialize the last update time
	enemy->accumulated_time = 0; // Accumulated time for updates
	// Initialize enemy sprites
	init_enemy_sprites(enemy);
	// Set a random direction for movement
	random_dir = rand() % 4;
	init_rand_dir_enemy(enemy, random_dir);
	enemy->next = NULL; // Initialize next enemy pointer to NULL
}

/**
 * Initializes the sprites used for different enemy states and directions.
 */
void	init_enemy_sprites(t_enemy *enemy)
{
	// Set the image paths for the enemy's different states and directions
	enemy->dead = (BLOOD);
	enemy->front_sprites[0] = (ENEMY_FRONT_STAND);
	enemy->front_sprites[1] = (ENEMY_FRONT_MV1);
	enemy->front_sprites[2] = (ENEMY_FRONT_MV2);
	enemy->back_sprites[0] = (ENEMY_BACK_MV1);
	enemy->back_sprites[1] = (ENEMY_BACK_MV2);
	enemy->back_sprites[2] = (ENEMY_BACK_MV3);
	enemy->left_sprites[0] = (ENEMY_LEFT_MV1);
	enemy->left_sprites[1] = (ENEMY_LEFT_MV2);
	enemy->left_sprites[2] = (ENEMY_LEFT_MV3);
	enemy->right_sprites[0] = (ENEMY_RIGHT_MV1);
	enemy->right_sprites[1] = (ENEMY_RIGHT_MV2);
	enemy->right_sprites[2] = (ENEMY_RIGHT_MV3);
}

/**
 * Initializes the random direction for enemy movement based on a random number.
 */
void	init_rand_dir_enemy(t_enemy *enemy, int random_dir)
{
	// Set the enemy's movement direction based on the random number
	if (random_dir == 0)
		enemy->mv_dir = DIR_UP;
	else if (random_dir == 1)
		enemy->mv_dir = DIR_DOWN;
	else if (random_dir == 2)
		enemy->mv_dir = DIR_LEFT;
	else
		enemy->mv_dir = DIR_RIGHT;
}

/**
 * Allocates and initializes memory for a new enemy.
 * Returns a pointer to the new enemy or NULL if allocation fails.
 */
t_enemy	*new_enemy(void)
{
	t_enemy	*new_enemy;

	// Allocate memory for the new enemy
	new_enemy = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
	if (!new_enemy)
	{
		ft_printf("Error allocating memory for a new enemy.\n"); // Error message
		return (0); // Return NULL if allocation fails
	}
	new_enemy->next = NULL; // Initialize next enemy pointer to NULL
	return (new_enemy); // Return the newly created enemy
}
