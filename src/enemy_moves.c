/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:19:12 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Checks if the enemy can move to a new position.
 * Updates the enemy's movement direction if the move is valid.
 * Returns 1 if the move is possible, 0 otherwise.
 */
int	move_enemys_check(t_game *game, t_enemy *eny, int dx, int dy)
{
	int	new_x;
	int	new_y;

	if (!eny->is_alive)
		return (0); // Enemy is not alive, cannot move

	// Calculate new position
	new_x = eny->eny_p.x + dx * SZ;
	new_y = eny->eny_p.y + dy * SZ;

	// Check if the new position is a wall, collectable, exit, or another enemy
	if (game->map.map[new_y / SZ][new_x / SZ].type == '1' || 
		game->map.map[new_y / SZ][new_x / SZ].type == 'C' ||
		game->map.map[new_y / SZ][new_x / SZ].type == 'E' ||
		game->map.map[new_y / SZ][new_x / SZ].type == 'M')
		return (0); // Move is blocked

	// Set the movement direction based on dx and dy
	if (dx == 0 && dy == -1)
		eny->mv_dir = DIR_UP;
	else if (dx == 0 && dy == 1)
		eny->mv_dir = DIR_DOWN;
	else if (dx == -1 && dy == 0)
		eny->mv_dir = DIR_LEFT;
	else if (dx == 1 && dy == 0)
		eny->mv_dir = DIR_RIGHT;

	return (1); // Move is possible
}

/**
 * Moves the enemy in the specified direction.
 * Updates enemy's position and sets up movement parameters.
 */
void	move_enemy(t_game *game, t_enemy *eny, int dx, int dy)
{
	t_pos	old_pos;
	t_pos	new_pos;

	if (eny->is_moving)
		return ; // Enemy is already moving, cannot start new movement

	// Record the old position
	old_pos.x = eny->eny_p.x;
	old_pos.y = eny->eny_p.y;

	// Set movement parameters
	eny->dx = dx;
	eny->dy = dy;
	eny->steps_remaining = 10; // Number of steps to move
	eny->step_size = 4; // Size of each step
	eny->update_interval = 1000 / 60; // Update interval for animation

	// Calculate new destination position
	new_pos.x = eny->eny_p.x + dx * 20 * 2;
	new_pos.y = eny->eny_p.y + dy * 20 * 2;
	eny->dest_p = new_pos;

	// Initialize timing and animation
	eny->last_update_time = clock();
	eny->accumulated_time = 0;
	eny->current_sprite = 0;
	eny->is_moving = 1; // Set moving flag to true

	// Update map to reflect enemy's new position
	update_map_tiles(game, old_pos, new_pos, 'M');
}

/**
 * Updates the enemy's position based on elapsed time and movement parameters.
 */
void	update_enemy_position(t_enemy *eny)
{
	clock_t	current_time;
	int		elapsed_time;
	int		time_per_step;

	current_time = clock(); // Get current time
	elapsed_time = (current_time - eny->last_update_time) * 1000 / CLOCKS_PER_SEC; // Calculate elapsed time
	eny->accumulated_time += elapsed_time; // Update accumulated time
	time_per_step = eny->update_interval;

	// Move enemy step-by-step based on elapsed time
	while (eny->accumulated_time >= time_per_step && eny->steps_remaining > 0)
	{
		eny->eny_p.x += eny->dx * eny->step_size;
		eny->eny_p.y += eny->dy * eny->step_size;
		eny->steps_remaining--;
		eny->current_sprite = (eny->current_sprite + 1) % 3; // Update sprite for animation
		eny->accumulated_time -= time_per_step; // Reduce accumulated time
	}

	if (eny->steps_remaining == 0)
	{
		eny->is_moving = 0; // Stop moving when steps are finished
		eny->current_sprite = 0; // Reset sprite
	}

	// Update last update time
	eny->last_update_time = current_time;
}

/**
 * Moves all enemies randomly and checks if they can move in the chosen direction.
 */
void	move_rand_enemys(t_game *game)
{
	t_enemy	*cur_eny;
	int		directions[4][2];
	int		dir_index;
	int		dx;
	int		dy;

	cur_eny = game->eny;
	init_directions(directions); // Initialize movement directions

	while (cur_eny != NULL)
	{
		if (cur_eny->is_alive && rand() % 2 == 0)
		{
			dir_index = rand() % 4; // Choose a random direction
			dx = directions[dir_index][0];
			dy = directions[dir_index][1];
			if (move_enemys_check(game, cur_eny, dx, dy))
			{
				move_enemy(game, cur_eny, dx, dy); // Move enemy if the move is valid
			}
		}
		cur_eny = cur_eny->next; // Move to the next enemy
	}
}

/**
 * Randomly updates the sprites of all enemies.
 */
void	update_enemy_sprite_randomly(t_game *game)
{
	t_enemy		*current_enemy;
	static int	frame_counter;

	frame_counter++; // Increment frame counter
	if (frame_counter >= 180)
	{
		current_enemy = game->eny;
		while (current_enemy != NULL)
		{
			if (rand() % 20)
			{
				current_enemy->mv_dir = rand() % 4; // Set a random movement direction
				put_enemy(game, current_enemy, current_enemy->current_sprite); // Update enemy sprite
			}
			current_enemy = current_enemy->next; // Move to the next enemy
		}
		frame_counter = 0; // Reset frame counter
	}
}
