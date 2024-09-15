#include "../include/so_long.h"

/**
 * Initializes the player with default values and settings.
 * Sets the player's starting position, movement direction, and other properties.
 * 
 * @param game A pointer to the game structure.
 */
void	init_player(t_game *game)
{
	game->p1.p1_p.x = game->map.start_p1_p.x; // Set the player's starting x-coordinate
	game->p1.p1_p.y = game->map.start_p1_p.y; // Set the player's starting y-coordinate
	game->p1.p1 = NULL; // Initialize player sprite to NULL
	game->p1.bl = NULL; // Initialize balloon sprite to NULL
	game->p1.alive = 1; // Set the player as alive
	game->p1.mv_dir = STAND; // Set the initial movement direction to stand
	game->p1.is_moving = 0; // Set the player as not moving
	game->p1.moves = 0; // Initialize the number of moves to 0
	game->p1.current_sprite = 0; // Initialize the current sprite index
	init_player_sprites(game); // Initialize player sprites
	game->p1.dx = 0; // Set the movement delta in the x-direction
	game->p1.dy = 0; // Set the movement delta in the y-direction
	game->p1.steps_remaining = 0; // Initialize the number of steps remaining
	game->p1.step_size = 0; // Initialize the step size
	game->p1.update_interval = 1000 / 60; // Set the update interval for animation
	game->p1.last_update_time = clock(); // Record the last update time
	game->p1.accumulated_time = 0; // Initialize accumulated time
	game->p1.dest_p = (t_pos){0, 0}; // Set the destination position to (0, 0)
}

/**
 * Initializes the sprites used for player animation and movement.
 * 
 * @param game A pointer to the game structure.
 */
void	init_player_sprites(t_game *game)
{
	game->p1.front_sprites[0] = (PLAYER_FRONT_STAND); // Sprite for standing front
	game->p1.front_sprites[1] = (PLAYER_FRONT_MV1); // Sprite for moving front (1)
	game->p1.front_sprites[2] = (PLAYER_FRONT_MV2); // Sprite for moving front (2)
	game->p1.back_sprites[0] = (PLAYER_BACK_MV1); // Sprite for moving back (1)
	game->p1.back_sprites[1] = (PLAYER_BACK_MV2); // Sprite for moving back (2)
	game->p1.back_sprites[2] = (PLAYER_BACK_MV3); // Sprite for moving back (3)
	game->p1.left_sprites[0] = (PLAYER_LEFT_MV1); // Sprite for moving left (1)
	game->p1.left_sprites[1] = (PLAYER_LEFT_MV2); // Sprite for moving left (2)
	game->p1.left_sprites[2] = (PLAYER_LEFT_MV3); // Sprite for moving left (3)
	game->p1.right_sprites[0] = (PLAYER_RIGHT_MV1); // Sprite for moving right (1)
	game->p1.right_sprites[1] = (PLAYER_RIGHT_MV2); // Sprite for moving right (2)
	game->p1.right_sprites[2] = (PLAYER_RIGHT_MV3); // Sprite for moving right (3)
	game->p1.pl_ballom = (PLAYER_BALLOM); // Sprite for balloon display
}

/**
 * Updates and displays the player sprite based on the current movement direction and sprite index.
 * 
 * @param game A pointer to the game structure.
 * @param sprite_index The index of the sprite to display.
 */
void	put_player(t_game *game, int sprite_index)
{
	char	*current_sprite;
	t_pos	pos;

	pos = game->p1.p1_p; // Get the player's current position
	if (game->p1.alive)
	{
		if (sprite_index < 0 || sprite_index >= 3)
			sprite_index = 0; // Ensure the sprite index is within valid range
		if (game->p1.mv_dir == DIR_UP)
			current_sprite = game->p1.back_sprites[sprite_index]; // Choose the back sprite if moving up
		else if (game->p1.mv_dir == DIR_DOWN)
			current_sprite = game->p1.front_sprites[sprite_index]; // Choose the front sprite if moving down
		else if (game->p1.mv_dir == DIR_LEFT)
			current_sprite = game->p1.left_sprites[sprite_index]; // Choose the left sprite if moving left
		else if (game->p1.mv_dir == DIR_RIGHT)
			current_sprite = game->p1.right_sprites[sprite_index]; // Choose the right sprite if moving right
		else
			current_sprite = PLAYER_FRONT_STAND; // Default to standing sprite if no direction
	}
	else
		current_sprite = PDEAD; // Set the sprite to dead if the player is not alive
	game->p1.p1 = create_sprite(game, current_sprite); // Create the sprite based on the current state
	create_character(game->p1.p1, game, pos.x, pos.y); // Display the player sprite at the current position
	if (game->p1.p1)
		destroy_sprite(&game->p1.p1, game->mlx); // Destroy the sprite after displaying to avoid memory leaks
}
