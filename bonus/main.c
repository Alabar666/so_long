/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:44 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:33:25 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Initializes the world and sets up the game.
 * 
 * @param game A pointer to the game structure.
 */
static void	start_world(t_game *game);

int	main(int ac, char **av)
{
	t_game	game;

	// Check for correct number of arguments.
	if (ac == 2 && av[1])
	{
		srand(time(NULL)); // Seed the random number generator.
		init_game(&game); // Initialize the game structure.
		map_start(av[1], &game); // Load and initialize the map.
		start_world(&game); // Set up the world.
		battle_load(&game); // Load battle resources.
		init_player(&game); // Initialize the player.
		create_map(&game); // Create the map in the game.
		update_frame(&game); // Update the game frame.
		
		// Set up event hooks.
		mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
		mlx_hook(game.win, DestroyNotify, 0L, gameover, &game);
		mlx_loop_hook(game.mlx, game_loop_hook, &game);
		
		mlx_loop(game.mlx); // Enter the event loop.
		
		// Clean up resources after exiting the event loop.
		mlx_destroy_image(game.mlx, game.world);
		mlx_destroy_window(game.mlx, game.win);
		mlx_destroy_display(game.mlx);
		free(game.mlx);
	}
	
	// Print an error message if arguments are invalid.
	return (write(2, "Error\nInvalid input\n", 21));
}

/**
 * Allocates and initializes the world sprite.
 * 
 * @param game A pointer to the game structure.
 */
static void	start_world(t_game *game)
{
	t_sprite	*world;

	world = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!world)
	{
		ft_printf("Error\nFailed to allocate memory for world\n");
		return ;
	}
	
	// Create a new image for the world with the map's dimensions.
	world->img = mlx_new_image(game->mlx, game->map.colun * SZ, game->map.lines * SZ);
	if (!world->img)
	{
		gameover(game); // Clean up and exit if image creation fails.
		return ;
	}
	
	// Get image data address.
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->width = game->map.colun * SZ;
	world->height = game->map.lines * SZ;
	game->world = world; // Assign the world sprite to the game structure.
}

/**
 * Loads battle resources.
 * 
 * @param game A pointer to the game structure.
 */
void	battle_load(t_game *game)
{
	t_sprite	*battle;

	init_battle(game); // Initialize battle-related settings.
	
	battle = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!battle)
	{
		ft_printf("Error\nFailed to allocate memory for battle\n");
		gameover(game); // Clean up and exit if allocation fails.
	}
	
	// Create a new image for the battle screen.
	battle->img = mlx_new_image(game->mlx, 630, 500);
	if (!battle->img)
	{
		ft_printf("Error\nFailed to allocate memory for battle\n");
		gameover(game); // Clean up and exit if image creation fails.
	}
	
	// Get image data address.
	battle->addr = mlx_get_data_addr(battle->img, &battle->bits_per_pixel,
			&battle->line_length, &battle->endian);
	game->battle.btl_img = battle; // Assign the battle sprite to the game structure.
	
	// Destroy the image and free the sprite (temporary battle image).
	mlx_destroy_image(game->mlx, battle->img);
	free(battle);
}

/**
 * Game loop hook function that updates the frame and manages battle state.
 * 
 * @param game A pointer to the game structure.
 * @return An integer value indicating success or failure.
 */
int	game_loop_hook(t_game *game)
{
	if (!game->is_paused)
		update_frame(game); // Update the game frame if not paused.
	if (game->battle.is_running)
		create_battle_screen(game); // Create the battle screen if the battle is running.
	return (0);
}
