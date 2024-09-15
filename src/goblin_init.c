/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:01:22 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:31:33 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the goblin list to NULL.
 * 
 * @param game A pointer to the game structure.
 */
void	init_list_goblin(t_game *game)
{
	game->gbl = NULL; // Set the goblin list to NULL
}

/**
 * Adds a new goblin to the end of the goblin list.
 * 
 * @param game A pointer to the game structure.
 * @param x The x-coordinate of the new goblin.
 * @param y The y-coordinate of the new goblin.
 */
void	add_goblin_to_list(t_game *game, int x, int y)
{
	t_goblin	*nw_goblin;
	t_goblin	*current;

	nw_goblin = new_goblin(); // Create a new goblin
	if (!nw_goblin)
	{
		ft_printf("Error creating goblin.\n"); // Print an error message if creation fails
		free_goblins(game->gbl); // Free any existing goblins
		return ;
	}
	init_goblin(nw_goblin); // Initialize the new goblin
	nw_goblin->gbl_p.x = x; // Set goblin position
	nw_goblin->gbl_p.y = y;
	if (game->gbl == NULL)
	{
		game->gbl = nw_goblin; // Set as the first goblin if the list is empty
	}
	else
	{
		current = game->gbl;
		while (current->next != NULL)
			current = current->next; // Traverse to the end of the list
		current->next = nw_goblin; // Add the new goblin to the end
	}
}

/**
 * Initializes the properties of a goblin.
 * 
 * @param goblin A pointer to the goblin structure.
 */
void	init_goblin(t_goblin *goblin)
{
	int	random_dir;

	goblin->gbl_p = (t_pos){0, 0}; // Initialize position to (0, 0)
	goblin->dest_p = (t_pos){0, 0}; // Initialize destination position
	goblin->gbl = NULL; // Initialize goblin sprite
	goblin->is_alive = 1; // Set goblin to alive
	goblin->current_sprite = 0; // Set initial sprite index
	goblin->is_moving = 0; // Set goblin to not moving
	goblin->dx = 0; // Initialize movement direction
	goblin->dy = 0;
	goblin->steps_remaining = 0; // Initialize step count
	goblin->step_size = 0; // Initialize step size
	goblin->update_interval = 1000 / 60; // Set update interval for sprite animation
	goblin->last_update_time = clock(); // Record the last update time
	goblin->accumulated_time = 0; // Initialize accumulated time
	init_goblin_sprites(goblin); // Initialize goblin sprites
	random_dir = rand() % 4; // Generate a random direction
	init_rand_dir_goblin(goblin, random_dir); // Set the goblin's direction
	goblin->next = NULL; // Initialize the next pointer
}

/**
 * Initializes the sprites for the goblin.
 * 
 * @param goblin A pointer to the goblin structure.
 */
void	init_goblin_sprites(t_goblin *goblin)
{
	goblin->dead = (BLOOD); // Set the sprite for the dead goblin
	goblin->front_sprites[0] = (GOBLIN_FRONT_STAND); // Front standing sprite
	goblin->front_sprites[1] = (GOBLIN_FRONT_MV1); // Front moving sprite 1
	goblin->front_sprites[2] = (GOBLIN_FRONT_MV2); // Front moving sprite 2
	goblin->back_sprites[0] = (GOBLIN_BACK_MV1); // Back moving sprite 1
	goblin->back_sprites[1] = (GOBLIN_BACK_MV2); // Back moving sprite 2
	goblin->back_sprites[2] = (GOBLIN_BACK_MV3); // Back moving sprite 3
	goblin->left_sprites[0] = (GOBLIN_LEFT_MV1); // Left moving sprite 1
	goblin->left_sprites[1] = (GOBLIN_LEFT_MV2); // Left moving sprite 2
	goblin->left_sprites[2] = (GOBLIN_LEFT_MV3); // Left moving sprite 3
	goblin->right_sprites[0] = (GOBLIN_RIGHT_MV1); // Right moving sprite 1
	goblin->right_sprites[1] = (GOBLIN_RIGHT_MV2); // Right moving sprite 2
	goblin->right_sprites[2] = (GOBLIN_RIGHT_MV3); // Right moving sprite 3
}

/**
 * Sets a random direction for the goblin.
 * 
 * @param goblin A pointer to the goblin structure.
 * @param random_dir An integer representing the random direction.
 */
void	init_rand_dir_goblin(t_goblin *goblin, int random_dir)
{
	if (random_dir == 0)
		goblin->mv_dir = DIR_UP; // Set direction to up
	else if (random_dir == 1)
		goblin->mv_dir = DIR_DOWN; // Set direction to down
	else if (random_dir == 2)
		goblin->mv_dir = DIR_LEFT; // Set direction to left
	else
		goblin->mv_dir = DIR_RIGHT; // Set direction to right
}
