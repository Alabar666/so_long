/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:16:00 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 19:16:04 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_game(t_game *game)
{
	render_background(game);
	render_goblins(game);
	render_enemies(game);
	render_player_and_extras(game);
	mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);
	if (game->p1.moves != 0)
		put_moves(game);
}

void	render_background(t_game *game)
{
	put_map(game);
	put_exit(game);
	if (!game->p1.alive)
		put_dead(game);
}

void	render_goblins(t_game *game)
{
	t_goblin	*current_goblin;

	current_goblin = game->gbl;
	while (current_goblin != NULL)
	{
		put_goblin(game, current_goblin, current_goblin->current_sprite);
		current_goblin = current_goblin->next;
	}
}

void	render_enemies(t_game *game)
{
	t_enemy	*current_enemy;

	current_enemy = game->eny;
	while (current_enemy != NULL)
	{
		put_enemy(game, current_enemy, current_enemy->current_sprite);
		current_enemy = current_enemy->next;
	}
}

void	render_player_and_extras(t_game *game)
{
	if (game->p1.alive)
	{
		update_goblin_sprite_randomly(game);
		update_enemy_sprite_randomly(game);
	}
	put_player(game, game->p1.current_sprite);
	put_moves(game);
}
