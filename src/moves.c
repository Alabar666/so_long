#include "../include/so_long.h"

/**
 * Handles key press events to determine whether to end the game, handle battle actions,
 * or process player movement.
 * 
 * @param key The key code of the pressed key.
 * @param game A pointer to the game structure.
 * @return 0 if the event is handled, otherwise non-zero.
 */
int	key_pressed(int key, t_game *game)
{
	if (key == ESC && !game->is_paused)
	{
		gameover(game); // End the game if ESC is pressed and the game is not paused
		return (0);
	}
	if (game->battle.is_running)
		return (handle_battle_keys(key, game)); // Handle battle key events if in battle mode
	else
		return (handle_player_movement(key, game)); // Handle player movement otherwise
}

/**
 * Processes player movement based on the key pressed.
 * 
 * @param key The key code of the pressed key.
 * @param game A pointer to the game structure.
 * @return 0 if the event is handled, otherwise non-zero.
 */
int	handle_player_movement(int key, t_game *game)
{
	if (game->p1.is_moving || !game->p1.alive)
		return (0); // Do nothing if the player is already moving or is not alive
	else if (key == KEY_W || key == UP)
	{
		// Check if the tile above the player is not a wall
		if (game->map.map[(game->p1.p1_p.y / SZ) - 1][game->p1.p1_p.x / SZ].type != '1')
			return (game->p1.mv_dir = DIR_UP, move_player(game, 0, -1), 0); // Move player up if valid
	}
	else if (key == KEY_S || key == DOWN)
	{
		// Check if the tile below the player is not a wall
		if (game->map.map[(game->p1.p1_p.y / SZ) + 1][game->p1.p1_p.x / SZ].type != '1')
			return (game->p1.mv_dir = DIR_DOWN, move_player(game, 0, +1), 0); // Move player down if valid
	}
	else if (key == KEY_A || key == LEFT)
	{
		// Check if the tile to the left of the player is not a wall
		if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) - 1].type != '1')
			return (game->p1.mv_dir = DIR_LEFT, move_player(game, -1, 0), 0); // Move player left if valid
	}
	else if (key == KEY_D || key == RIGHT)
	{
		// Check if the tile to the right of the player is not a wall
		if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) + 1].type != '1')
			return (game->p1.mv_dir = DIR_RIGHT, move_player(game, 1, 0), 0); // Move player right if valid
	}
	return (0);
}

/**
 * Handles key presses during a battle scenario.
 * 
 * @param key The key code of the pressed key.
 * @param game A pointer to the game structure.
 * @return 0 if the event is handled, otherwise non-zero.
 */
int	handle_battle_keys(int key, t_game *game)
{
	if (key == ENTER || key == SPACE)
	{
		if (game->run_selected)
		{
			// Display a message if the "Run" option is selected
			game->message_display_duration = 0;
			while (game->message_display_duration++ < 700000)
			{
				mlx_string_put(game->mlx, game->win, (game->world->width - 200)
					/ 2, (game->world->height - 50) / 2, 0xFFFF00,
					"The Goblin will not allow you to escape.");
			}
			return (0);
		}
		else
		{
			// Close the battle if "Fight" is selected
			game->wait_input = 0;
			close_battle(game);
			return (0);
		}
	}
	return (battle_keys(key, game), 0); // Handle other battle keys
}

/**
 * Moves the player character by updating their position and handling movement animations.
 * 
 * @param game A pointer to the game structure.
 * @param dx The change in x-coordinate (direction of movement).
 * @param dy The change in y-coordinate (direction of movement).
 */
void	move_player(t_game *game, int dx, int dy)
{
	t_pos	old_pos;
	t_pos	new_pos;

	if (game->p1.is_moving)
		return ; // Do nothing if the player is already moving
	old_pos.x = game->p1.p1_p.x;
	old_pos.y = game->p1.p1_p.y;
	game->p1.dx = dx; // Set direction of movement in x
	game->p1.dy = dy; // Set direction of movement in y
	game->p1.steps_remaining = 10; // Number of steps for the movement animation
	game->p1.step_size = 4; // Size of each movement step
	game->p1.update_interval = 1000 / 60; // Interval between updates in milliseconds
	new_pos.x = game->p1.p1_p.x + dx * 20 * 2; // Calculate new x position
	new_pos.y = game->p1.p1_p.y + dy * 20 * 2; // Calculate new y position
	game->p1.dest_p = new_pos; // Set destination position
	game->p1.last_update_time = clock(); // Record the current time
	game->p1.accumulated_time = 0; // Initialize accumulated time
	game->p1.current_sprite = 0; // Set the initial sprite
	game->p1.is_moving = 1; // Indicate that the player is moving
	game->p1.moves++; // Increment move count
	ft_printf("Moves amount: %i\n", game->p1.moves); // Print move count
	put_moves(game); // Update the display with new moves
	check_position(game, game->p1.dest_p.x, game->p1.dest_p.y); // Check the new position
	update_map_tiles(game, old_pos, new_pos, 'P'); // Update map with new player position
	check_for_overlap(game); // Check for overlaps with other entities
}

/**
 * Updates the player's position based on elapsed time and remaining steps.
 * 
 * @param game A pointer to the game structure.
 */
void	update_player_position(t_game *game)
{
	int		elapsed_time;
	int		time_per_step;
	clock_t	current_time;

	current_time = clock(); // Get the current time
	elapsed_time = (current_time - game->p1.last_update_time) * 1000
		/ CLOCKS_PER_SEC; // Calculate elapsed time in milliseconds
	game->p1.accumulated_time += elapsed_time; // Add elapsed time to accumulated time
	time_per_step = game->p1.update_interval; // Time required for each step
	while (game->p1.accumulated_time >= time_per_step
		&& game->p1.steps_remaining > 0)
	{
		game->p1.p1_p.x += game->p1.dx * game->p1.step_size; // Update x position
		game->p1.p1_p.y += game->p1.dy * game->p1.step_size; // Update y position
		game->p1.steps_remaining--; // Decrease remaining steps
		game->p1.current_sprite = (game->p1.current_sprite + 1) % 3; // Cycle through sprites
		game->p1.accumulated_time -= time_per_step; // Subtract the time used for this step
	}
	if (game->p1.steps_remaining == 0)
	{
		game->p1.is_moving = 0; // Stop moving if all steps are completed
		game->p1.current_sprite = 0; // Reset sprite
	}
	game->p1.last_update_time = current_time; // Update the last update time
	check_for_overlap(game); // Check for overlaps with other entities
}
