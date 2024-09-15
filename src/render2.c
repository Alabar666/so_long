#include "../include/so_long.h"

/**
 * Renders the game by drawing all elements to the window.
 * 
 * @param game A pointer to the game structure.
 */
void	render_game(t_game *game)
{
	render_background(game); // Render the background elements such as the map and exit
	render_goblins(game); // Render all goblins in the game
	render_enemies(game); // Render all enemies in the game
	render_player_and_extras(game); // Render the player and any additional elements
	mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0); // Draw the updated game world image to the window
	if (game->p1.moves != 0) // If the player has made any moves
		put_moves(game); // Display the moves counter
}

/**
 * Renders the background elements of the game, such as the map and exit.
 * 
 * @param game A pointer to the game structure.
 */
void	render_background(t_game *game)
{
	put_map(game); // Draw the game map
	put_exit(game); // Draw the exit point
	if (!game->p1.alive) // If the player is dead
		put_dead(game); // Render the dead player state
}

/**
 * Renders all goblins present in the game.
 * 
 * @param game A pointer to the game structure.
 */
void	render_goblins(t_game *game)
{
	t_goblin	*current_goblin; // Pointer to the current goblin in the list

	current_goblin = game->gbl; // Start with the first goblin
	while (current_goblin != NULL) // Iterate over all goblins
	{
		put_goblin(game, current_goblin, current_goblin->current_sprite); // Draw the current goblin with its sprite
		current_goblin = current_goblin->next; // Move to the next goblin
	}
}

/**
 * Renders all enemies present in the game.
 * 
 * @param game A pointer to the game structure.
 */
void	render_enemies(t_game *game)
{
	t_enemy	*current_enemy; // Pointer to the current enemy in the list

	current_enemy = game->eny; // Start with the first enemy
	while (current_enemy != NULL) // Iterate over all enemies
	{
		put_enemy(game, current_enemy, current_enemy->current_sprite); // Draw the current enemy with its sprite
		current_enemy = current_enemy->next; // Move to the next enemy
	}
}

/**
 * Renders the player and any additional elements such as the moves counter.
 * 
 * @param game A pointer to the game structure.
 */
void	render_player_and_extras(t_game *game)
{
	if (game->p1.alive) // If the player is alive
	{
		update_goblin_sprite_randomly(game); // Update goblin sprites randomly for animation
		update_enemy_sprite_randomly(game); // Update enemy sprites randomly for animation
	}
	put_player(game, game->p1.current_sprite); // Draw the player with the current sprite
	put_moves(game); // Display the moves counter
}
