/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:02:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:32:15 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Checks if a goblin can move to a new position.
 * 
 * @param game A pointer to the game structure.
 * @param gbl A pointer to the goblin structure.
 * @param dx The change in x-coordinate.
 * @param dy The change in y-coordinate.
 * 
 * @return 1 if the goblin can move, 0 otherwise.
 */
int	move_goblins_check(t_game *game, t_goblin *gbl, int dx, int dy)
{
	int	new_x;
	int	new_y;

	if (!gbl->is_alive)
		return (0); // Return 0 if the goblin is not alive

	// Calculate the new position
	new_x = gbl->gbl_p.x + dx * SZ;
	new_y = gbl->gbl_p.y + dy * SZ;

	// Check if the new position is a wall ('1'), collectable ('C'), exit ('E'), or another goblin ('M')
	if (game->map.map[new_y / SZ][new_x / SZ].type == '1' ||
		game->map.map[new_y / SZ][new_x / SZ].type == 'C' ||
		game->map.map[new_y / SZ][new_x / SZ].type == 'E' ||
		game->map.map[new_y / SZ][new_x / SZ].type == 'M')
		return (0);

	// Update the goblin's movement direction
	if (dx == 0 && dy == -1)
		gbl->mv_dir = DIR_UP;
	else if (dx == 0 && dy == 1)
		gbl->mv_dir = DIR_DOWN;
	else if (dx == -1 && dy == 0)
		gbl->mv_dir = DIR_LEFT;
	else if (dx == 1 && dy == 0)
		gbl->mv_dir = DIR_RIGHT;

	return (1); // Return 1 if the move is valid
}

/**
 * Moves a goblin to a new position.
 * 
 * @param game A pointer to the game structure.
 * @param gbl A pointer to the goblin structure.
 * @param dx The change in x-coordinate.
 * @param dy The change in y-coordinate.
 */
void	move_goblin(t_game *game, t_goblin *gbl, int dx, int dy)
{
	t_pos	old_pos;
	t_pos	new_pos;

	if (gbl->is_moving)
		return ; // Return if the goblin is already moving

	old_pos.x = gbl->gbl_p.x;
	old_pos.y = gbl->gbl_p.y;
	gbl->dx = dx;
	gbl->dy = dy;
	gbl->steps_remaining = 10; // Number of steps to take
	gbl->step_size = 4; // Size of each step
	gbl->update_interval = 1000 / 60; // Update interval for sprite animation
	new_pos.x = gbl->gbl_p.x + dx * 20 * 2;
	new_pos.y = gbl->gbl_p.y + dy * 20 * 2;
	gbl->dest_p = new_pos;
	gbl->last_update_time = clock(); // Record the time when movement started
	gbl->accumulated_time = 0; // Initialize accumulated time
	gbl->current_sprite = 0; // Set the initial sprite
	gbl->is_moving = 1; // Set the goblin as moving

	// Update the map tiles and check for overlaps
	update_map_tiles(game, old_pos, new_pos, 'C');
	check_for_overlap(game);
	destroy_sprite(&game->gbl->gbl, game->mlx); // Destroy the old goblin sprite
}

/**
 * Updates the position and sprite of a goblin based on elapsed time.
 * 
 * @param gbl A pointer to the goblin structure.
 */
void	update_goblin_position(t_goblin *gbl)
{
	clock_t	current_time;
	int		elapsed_time;
	int		time_per_step;

	current_time = clock(); // Get the current time
	elapsed_time = (current_time - gbl->last_update_time) * 1000 / CLOCKS_PER_SEC; // Calculate elapsed time
	gbl->accumulated_time += elapsed_time;
	time_per_step = gbl->update_interval;

	// Move the goblin and update the sprite based on accumulated time
	while (gbl->accumulated_time >= time_per_step && gbl->steps_remaining > 0)
	{
		gbl->gbl_p.x += gbl->dx * gbl->step_size;
		gbl->gbl_p.y += gbl->dy * gbl->step_size;
		gbl->steps_remaining--;
		gbl->current_sprite = (gbl->current_sprite + 1) % 3; // Cycle through sprites
		gbl->accumulated_time -= time_per_step;
	}

	// Stop the goblin from moving when all steps are completed
	if (gbl->steps_remaining == 0)
	{
		gbl->is_moving = 0;
		gbl->current_sprite = 0;
	}

	gbl->last_update_time = current_time; // Update the last update time
}

/**
 * Moves all goblins randomly.
 * 
 * @param game A pointer to the game structure.
 */
void	move_rand_goblins(t_game *game)
{
	t_goblin	*cur_gbl;
	int			directions[4][2];
	int			dir_index;
	int			dx;
	int			dy;

	cur_gbl = game->gbl;
	init_directions(directions); // Initialize possible movement directions

	while (cur_gbl != NULL)
	{
		if (cur_gbl->is_alive && rand() % 6 == 0) // Randomly decide whether to move
		{
			dir_index = rand() % 4; // Pick a random direction
			dx = directions[dir_index][0];
			dy = directions[dir_index][1];

			if (move_goblins_check(game, cur_gbl, dx, dy))
			{
				move_goblin(game, cur_gbl, dx, dy); // Move the goblin if the move is valid
			}
		}
		cur_gbl = cur_gbl->next; // Move to the next goblin in the list
	}
}

/**
 * Randomly updates the sprite of goblins.
 * 
 * @param game A pointer to the game structure.
 */
void	update_goblin_sprite_randomly(t_game *game)
{
	t_goblin	*current_goblin;
	static int	frame_counter = 0;

	frame_counter++; // Increment frame counter
	if (frame_counter >= 180) // Update every 180 frames
	{
		current_goblin = game->gbl;
		while (current_goblin != NULL)
		{
			if (rand() % 20) // Randomly decide whether to change the sprite
			{
				current_goblin->mv_dir = rand() % 4; // Pick a random direction
				put_goblin(game, current_goblin, current_goblin->current_sprite); // Update the goblin sprite
			}
			current_goblin = current_goblin->next; // Move to the next goblin in the list
		}
		frame_counter = 0; // Reset frame counter
	}
}
