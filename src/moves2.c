#include "../include/so_long.h"

/**
 * Updates the display to show the current number of moves.
 * It also displays a balloon sprite near the player if moves are not zero.
 * 
 * @param game A pointer to the game structure.
 */
void	put_moves(t_game *game)
{
	char	*move_str;
	int		balloon_x;
	int		balloon_y;
	int		text_x;
	int		text_y;

	move_str = ft_itoa(game->p1.moves); // Convert the number of moves to a string
	balloon_x = game->p1.p1_p.x + 40; // X coordinate for the balloon sprite
	balloon_y = game->p1.p1_p.y - 40; // Y coordinate for the balloon sprite
	text_x = balloon_x + 16; // X coordinate for the moves text
	text_y = balloon_y + 19; // Y coordinate for the moves text
	if (game->p1.moves != 0)
	{
		game->p1.bl = create_sprite(game, game->p1.pl_ballom); // Create a balloon sprite
		create_character(game->p1.bl, game, balloon_x, balloon_y); // Display the balloon sprite
		destroy_sprite(&game->p1.bl, game->mlx); // Destroy the sprite after displaying
	}
	mlx_string_put(game->mlx, game->win, text_x, text_y, 0xFFFF00, move_str); // Display the number of moves
	free(move_str); // Free the memory allocated for the move string
}

/**
 * Checks if the player's new position is within bounds and handles interactions with goblins and enemies.
 * 
 * @param game A pointer to the game structure.
 * @param dx The x-coordinate of the new position.
 * @param dy The y-coordinate of the new position.
 */
void	check_position(t_game *game, int dx, int dy)
{
	if (dx < 0 || dx >= game->map.width || dy < 0 || dy >= game->map.height)
		return ; // Exit if the new position is out of bounds
	handle_goblins(game, dx, dy); // Check and handle interactions with goblins
	handle_enemies_and_victory(game, dx, dy); // Check and handle interactions with enemies and victory conditions
}

/**
 * Handles interactions with goblins at the player's current position.
 * If a goblin is found, it starts a battle and updates the map accordingly.
 * 
 * @param game A pointer to the game structure.
 * @param dx The x-coordinate of the current position.
 * @param dy The y-coordinate of the current position.
 */
void	handle_goblins(t_game *game, int dx, int dy)
{
	t_goblin	*cur_gbl;
	char		enemy_type;

	cur_gbl = game->gbl; // Start with the first goblin
	enemy_type = game->map.map[dy / SZ][dx / SZ].type; // Get the type of the tile
	if (enemy_type != 'C' && enemy_type != 'M')
		return ; // Exit if the tile does not contain a goblin
	while (cur_gbl != NULL)
	{
		if (cur_gbl->gbl_p.x == dx && cur_gbl->gbl_p.y == dy
			&& cur_gbl->is_alive) // Check if there is an alive goblin at the position
		{
			cur_gbl->is_alive = 0; // Mark the goblin as dead
			game->map.map[dy / SZ][dx / SZ].type = 'B'; // Update the map to reflect the goblin's defeat
			game->map.goblin--; // Decrement the number of goblins
			start_battle(game, enemy_type); // Start a battle with the goblin
			break ; // Exit the loop after handling the goblin
		}
		cur_gbl = cur_gbl->next; // Move to the next goblin
	}
}

/**
 * Handles interactions with enemies and checks for victory conditions.
 * If the player encounters an enemy, a battle is started, and if all goblins are defeated, the game ends.
 * 
 * @param game A pointer to the game structure.
 * @param dx The x-coordinate of the current position.
 * @param dy The y-coordinate of the current position.
 */
void	handle_enemies_and_victory(t_game *game, int dx, int dy)
{
	char	enemy_type;

	enemy_type = game->map.map[dy / SZ][dx / SZ].type; // Get the type of the tile
	if (enemy_type == 'M')
	{
		start_battle(game, enemy_type); // Start a battle if the tile contains an enemy
		game->p1.p1 = create_sprite(game, PDEAD); // Set the player sprite to a dead state
		destroy_sprite(&game->p1.p1, game->mlx); // Destroy the sprite after setting
		game->p1.alive = 0; // Mark the player as dead
		game->map.map[dy / SZ][dx / SZ].type = '0'; // Update the map to reflect the player's defeat
		if (!game->wait_input && !game->p1.alive)
		{
			ft_printf("You are dead!\n"); // Print game over message
		}
	}
	if (game->map.goblin == 0 && enemy_type == 'E')
	{
		ft_printf("You saved the priestess!\n"); // Print victory message
		end_game(game); // End the game
	}
}

/**
 * Checks for overlaps between the player and goblins or enemies and handles them accordingly.
 * 
 * @param game A pointer to the game structure.
 */
void	check_for_overlap(t_game *game)
{
	t_pos		p1_pos;
	t_goblin	*cur_gbl;
	t_enemy		*cur_eny;

	p1_pos = game->p1.p1_p; // Get the player's current position
	cur_gbl = game->gbl; // Start with the first goblin
	while (cur_gbl != NULL)
	{
		if (cur_gbl->gbl_p.x == p1_pos.x && cur_gbl->gbl_p.y == p1_pos.y)
		{
			handle_goblins(game, p1_pos.x, p1_pos.y); // Handle interaction with the goblin
			break ; // Exit the loop after handling the goblin
		}
		cur_gbl = cur_gbl->next; // Move to the next goblin
	}
	cur_eny = game->eny; // Start with the first enemy
	while (cur_eny != NULL)
	{
		if (cur_eny->eny_p.x == p1_pos.x && cur_eny->eny_p.y == p1_pos.y)
		{
			handle_enemies_and_victory(game, p1_pos.x, p1_pos.y); // Handle interaction with the enemy
			break ; // Exit the loop after handling the enemy
		}
		cur_eny = cur_eny->next; // Move to the next enemy
	}
}
