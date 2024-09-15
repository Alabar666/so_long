/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:28:37 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Adds a new enemy to the end of the enemy list.
 * If the list is empty, the new enemy becomes the head of the list.
 */
void	add_enemy(t_enemy **head, t_enemy *new_enemy)
{
	t_enemy	*current;

	if (*head == NULL)
	{
		*head = new_enemy; // List is empty, so new enemy becomes head
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next; // Traverse to the end of the list
		current->next = new_enemy; // Append the new enemy to the end
	}
}

/**
 * Frees all memory allocated for enemies and their sprites.
 * Iterates through the list of enemies and deallocates each one.
 */
void	free_enemys(t_enemy *head)
{
	t_enemy	*current;
	t_enemy	*next;
	int		i;

	current = head;
	while (current != NULL)
	{
		next = current->next; // Save the next enemy
		i = -1;
		while (++i < 3)
		{
			// Free all sprite images for each direction
			free(current->front_sprites[i]);
			free(current->back_sprites[i]);
			free(current->left_sprites[i]);
			free(current->right_sprites[i]);
		}
		free(current->eny); // Free the current enemy's main sprite
		free(current); // Free the enemy structure itself
		current = next; // Move to the next enemy
	}
}

/**
 * Draws the enemy on the screen based on its current state and direction.
 * Updates the enemy's sprite based on its movement direction and current sprite index.
 */
void	put_enemy(t_game *game, t_enemy *enemy, int sprite_index)
{
	char	*current_sprite;
	t_pos	pos;

	pos = enemy->eny_p; // Get enemy's current position
	if (enemy->is_alive)
	{
		if (sprite_index < 0 || sprite_index >= 3)
			sprite_index = 0; // Ensure valid sprite index
		// Choose the correct sprite based on movement direction
		if (enemy->mv_dir == DIR_UP)
			current_sprite = enemy->back_sprites[sprite_index];
		else if (enemy->mv_dir == DIR_DOWN)
			current_sprite = enemy->front_sprites[sprite_index];
		else if (enemy->mv_dir == DIR_LEFT)
			current_sprite = enemy->left_sprites[sprite_index];
		else if (enemy->mv_dir == DIR_RIGHT)
			current_sprite = enemy->right_sprites[sprite_index];
		else
			current_sprite = enemy->front_sprites[0]; // Default sprite
	}
	else
		current_sprite = enemy->dead; // Use dead sprite if the enemy is not alive

	// Create and draw the enemy sprite on the screen
	enemy->eny = create_sprite(game, current_sprite);
	create_character(enemy->eny, game, pos.x, pos.y);
	if (enemy->eny)
		destroy_sprite(&enemy->eny, game->mlx); // Clean up sprite after drawing
}
