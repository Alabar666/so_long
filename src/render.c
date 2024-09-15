#include "../include/so_long.h"

/**
 * Updates the game frame, managing game updates and rendering based on time and pause state.
 * 
 * @param game A pointer to the game structure.
 * @return Always returns 0.
 */
int	update_frame(t_game *game)
{
	static clock_t	last_time = 0; // Static variable to store the last frame update time
	clock_t			current_time; // Current time
	float			delta_time; // Time difference between frames

	current_time = clock(); // Get the current time
	delta_time = (float)(current_time - last_time) / CLOCKS_PER_SEC; // Calculate the time difference in seconds
	if (delta_time >= 1.0f / 60.0f && !game->is_paused) // Check if enough time has passed for the next frame and if the game is not paused
	{
		if (!game->show_end_screen) // If the end screen is not being shown
		{
			update_game_elements(game, &last_time); // Update game elements
			render_game(game); // Render the game
		}
		else
		{
			render_end_screen(game); // Render the end screen
		}
	}
	return (0);
}

/**
 * Updates the game elements such as player position and global timer.
 * 
 * @param game A pointer to the game structure.
 * @param last_time A pointer to the last time the game was updated.
 */
void	update_game_elements(t_game *game, clock_t *last_time)
{
	clock_t	current_time; // Current time
	float	delta_time; // Time difference in seconds

	current_time = clock(); // Get the current time
	delta_time = (float)(current_time - *last_time) / CLOCKS_PER_SEC; // Calculate the time difference
	game->global_timer += delta_time; // Update the global timer
	update_player_position(game); // Update the player's position
	if (game->p1.alive) // If the player is alive
	{
		check_for_overlap(game); // Check for overlap with other game elements
	}
	*last_time = current_time; // Update the last time
}

/**
 * Updates the positions of goblins and enemies.
 * 
 * @param game A pointer to the game structure.
 */
void	update_positions(t_game *game)
{
	t_goblin	*cur_gbl; // Pointer to the current goblin
	t_enemy		*cur_eny; // Pointer to the current enemy

	cur_gbl = game->gbl; // Start with the first goblin
	while (cur_gbl != NULL) // Iterate over all goblins
	{
		update_goblin_position(cur_gbl); // Update the position of the current goblin
		cur_gbl = cur_gbl->next; // Move to the next goblin
	}
	cur_eny = game->eny; // Start with the first enemy
	while (cur_eny != NULL) // Iterate over all enemies
	{
		update_enemy_position(cur_eny); // Update the position of the current enemy
		cur_eny = cur_eny->next; // Move to the next enemy
	}
}

/**
 * Moves goblins and enemies randomly based on time intervals.
 * 
 * @param game A pointer to the game structure.
 */
void	move_randomly(t_game *game)
{
	if (difftime(time(NULL), game->lst_gbl_upt) >= 2.0) // If 2 seconds have passed since the last goblin update
	{
		move_rand_goblins(game); // Move goblins randomly
		game->lst_gbl_upt = time(NULL); // Update the last goblin update time
	}
	if (difftime(time(NULL), game->lst_eny_upt) >= 1.5) // If 1.5 seconds have passed since the last enemy update
	{
		move_rand_enemys(game); // Move enemies randomly
		game->lst_eny_upt = time(NULL); // Update the last enemy update time
	}
}

/**
 * Draws the game world by rendering a sprite at the given position.
 * 
 * @param sprite A pointer to the sprite structure.
 * @param game A pointer to the game structure.
 * @param posx The x-coordinate of the position where the sprite will be drawn.
 * @param posy The y-coordinate of the position where the sprite will be drawn.
 */
void	create_world(t_sprite *sprite, t_game *game, int posx, int posy)
{
	int				x; // X-coordinate in the sprite
	int				y; // Y-coordinate in the sprite
	unsigned int	color; // Color of the current pixel
	unsigned int	trans_color; // Transparent color to ignore

	trans_color = 0xFFC0CB; // Define the transparent color
	y = -1;
	while (++y < sprite->height) // Iterate over the sprite's height
	{
		x = -1;
		while (++x < sprite->width) // Iterate over the sprite's width
		{
			color = get_color_in_pixel(sprite, x, y); // Get the color of the current pixel
			if (color != trans_color) // If the color is not the transparent color
			{
				put_pixel(game->world, posx * SZ + x, posy * SZ + y, color); // Draw the pixel on the game world
			}
		}
	}
}
