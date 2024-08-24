/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 15:02:38 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	start_battle(t_game *game, char enemy_type)
{
	game->is_paused = 1;
	game->battle.is_running = 1;
	game->wait_input = 1;
	game->battle.enemy_type = enemy_type;
	if (enemy_type == 'C')
		game->battle.btl_img = create_sprite(game, CGBLATK);
	else if (enemy_type == 'M')
		game->battle.btl_img = create_sprite(game, CENYATK);
}

int	battle_loop_hook(t_game *game)
{
	if (game->battle.is_running)
		create_battle_screen(game);
	return (0);
}

void	battle_keys(int key, t_game *game)
{
	if (key == ESC)
	{
		close_battle(game);
		gameover(game);
	}
	else if (key == KEY_A || key == LEFT)
	{
		if (game->battle.btl_img)
			destroy_sprite(&game->battle.btl_img, game->mlx);
		if (game->battle.enemy_type == 'C')
			game->battle.btl_img = create_sprite(game, CGBLATK);
		else if (game->battle.enemy_type == 'M')
			game->battle.btl_img = create_sprite(game, CENYATK);
		game->run_selected = 0;
	}
	else if (key == KEY_D || key == RIGHT)
	{
		if (game->battle.btl_img)
			destroy_sprite(&game->battle.btl_img, game->mlx);
		if (game->battle.enemy_type == 'C')
			game->battle.btl_img = create_sprite(game, CGBLRUN);
		else if (game->battle.enemy_type == 'M')
			game->battle.btl_img = create_sprite(game, CENYRUN);
		game->run_selected = 1;
	}
}
