/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:44 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/22 20:18:14 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	start_world(t_game *game);

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2 && av[1])
	{
		srand(time(NULL));
		init_game(&game);
		map_start(av[1], &game);
		start_world(&game);
		battle_load(&game);
		init_player(&game);
		create_map(&game);
		update_frame(&game);
		mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
		mlx_hook(game.win, DestroyNotify, 0L, gameover, &game);
		mlx_loop_hook(game.mlx, game_loop_hook, &game);
		mlx_loop(game.mlx);
		mlx_destroy_image(game.mlx, game.world);
		mlx_destroy_window(game.mlx, game.win);
		mlx_destroy_display(game.mlx);
		free(game.mlx);
	}
	return (write(2, "Error\nInvalid input\n", 21));
}

static void	start_world(t_game *game)
{
	t_sprite	*world;

	world = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!world)
	{
		ft_printf("Error\nFailed to allocate memory for world\n");
		return ;
	}
	world->img = mlx_new_image(game->mlx, game->map.colun * SZ, game->map.lines
			* SZ);
	if (!world->img)
	{
		gameover(game);
		return;
	}
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->width = game->map.colun * SZ;
	world->height = game->map.lines * SZ;
	game->world = world;
}

void	battle_load(t_game *game)
{
	t_sprite	*battle;

	init_battle(game);
	battle = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!battle)
	{
		ft_printf("Error\nFailed to allocate memory for battle\n");
		gameover(game);
	}
	battle->img = mlx_new_image(game->mlx, 630, 500);
	if (!battle->img)
	{
		ft_printf("Error\nFailed to allocate memory for battle\n");
		gameover(game);
	}
	battle->addr = mlx_get_data_addr(battle->img, &battle->bits_per_pixel,
			&battle->line_length, &battle->endian);
	game->battle.btl_img = battle;
	mlx_destroy_image(game->mlx, battle->img);
	free(battle);
}

int	game_loop_hook(t_game	*game)
{
	if (!game->is_paused)
		update_frame(game);
	if (game->battle.is_running)
		create_battle_screen(game);
	return (0);
}
