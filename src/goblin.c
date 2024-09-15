/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:32:49 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Adds a new goblin to the end of the goblin list.
 * 
 * @param head A pointer to the head of the goblin list.
 * @param new_goblin A pointer to the new goblin to add.
 */
void	add_goblin(t_goblin **head, t_goblin *new_goblin)
{
	t_goblin	*current;

	if (*head == NULL)
	{
		*head = new_goblin; // If the list is empty, set the new goblin as the head.
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next; // Traverse to the end of the list.
		current->next = new_goblin; // Add the new goblin at the end.
	}
}

/**
 * Allocates memory for a new goblin and initializes it.
 * 
 * @return A pointer to the new goblin if allocation was successful, NULL otherwise.
 */
t_goblin	*new_goblin(void)
{
	t_goblin	*new_goblin;

	new_goblin = (t_goblin *)ft_calloc(1, sizeof(t_goblin));
	if (!new_goblin)
	{
		ft_printf("Error allocating memory for a new goblin.\n"); // Print an error message if allocation fails.
		return (0);
	}
	new_goblin->next = NULL; // Initialize the next pointer to NULL.
	return (new_goblin); // Return the newly created goblin.
}

/**
 * Frees all goblins in the list and their associated memory.
 * 
 * @param head A pointer to the head of the goblin list.
 */
void	free_goblins(t_goblin *head)
{
	t_goblin	*current;
	t_goblin	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next; // Save the pointer to the next goblin.
		free(current->gbl); // Free the goblin's sprite.
		free(current); // Free the goblin itself.
		current = next; // Move to the next goblin in the list.
	}
}

/**
 * Updates the position and sprite of a goblin on the screen.
 * 
 * @param game A pointer to the game structure.
 * @param goblin A pointer to the goblin to update.
 * @param sprite_index The index of the sprite to use.
 */
void	put_goblin(t_game *game, t_goblin *goblin, int sprite_index)
{
	char	*current_sprite;
	t_pos	pos;

	pos = goblin->gbl_p; // Get the current position of the goblin.
	if (goblin->is_alive)
	{
		// Select the appropriate sprite based on the goblin's movement direction.
		if (sprite_index < 0 || sprite_index >= 3)
			sprite_index = 0; // Ensure the sprite index is valid.
		if (goblin->mv_dir == DIR_UP)
			current_sprite = goblin->back_sprites[sprite_index];
		else if (goblin->mv_dir == DIR_DOWN)
			current_sprite = goblin->front_sprites[sprite_index];
		else if (goblin->mv_dir == DIR_LEFT)
			current_sprite = goblin->left_sprites[sprite_index];
		else if (goblin->mv_dir == DIR_RIGHT)
			current_sprite = goblin->right_sprites[sprite_index];
		else
			current_sprite = goblin->front_sprites[0]; // Default sprite if direction is invalid.
	}
	else
		current_sprite = goblin->dead; // Use the dead sprite if the goblin is not alive.

	// Create and position the goblin's sprite.
	goblin->gbl = create_sprite(game, current_sprite);
	create_character(goblin->gbl, game, pos.x, pos.y);
	
	// Destroy the goblin's sprite if it exists.
	if (goblin->gbl)
		destroy_sprite(&goblin->gbl, game->mlx);
}
