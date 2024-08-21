/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:10:30 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/21 20:55:31 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_game *game)
{
	game->p1.p1_p.x = game->map.start_p1_p.x;
	game->p1.p1_p.y = game->map.start_p1_p.y;
	game->p1.p1 = NULL;
    game->p1.bl = NULL;
	game->p1.alive = 1;
	game->p1.mv_dir = STAND;
	game->p1.is_moving = 0;
	game->p1.moves = 0;
	game->p1.current_sprite = 0;
	init_player_sprites(game);
	game->p1.dx = 0;
	game->p1.dy = 0;
	game->p1.steps_remaining = 0;
	game->p1.step_size = 0;
	game->p1.update_interval = 1000 / 60;
	game->p1.last_update_time = clock();
	game->p1.accumulated_time = 0;
	game->p1.p1 = NULL;
    game->p1.bl = NULL;
    game->p1.dest_p = (t_pos){0, 0};
}

void	init_player_sprites(t_game *game)
{
	game->p1.front_sprites[0] = ft_strdup(PLAYER_FRONT_STAND);
	game->p1.front_sprites[1] = ft_strdup(PLAYER_FRONT_MV1);
	game->p1.front_sprites[2] = ft_strdup(PLAYER_FRONT_MV2);
	game->p1.back_sprites[0] = ft_strdup(PLAYER_BACK_MV1);
	game->p1.back_sprites[1] = ft_strdup(PLAYER_BACK_MV2);
	game->p1.back_sprites[2] = ft_strdup(PLAYER_BACK_MV3);
	game->p1.left_sprites[0] = ft_strdup(PLAYER_LEFT_MV1);
	game->p1.left_sprites[1] = ft_strdup(PLAYER_LEFT_MV2);
	game->p1.left_sprites[2] = ft_strdup(PLAYER_LEFT_MV3);
	game->p1.right_sprites[0] = ft_strdup(PLAYER_RIGHT_MV1);
	game->p1.right_sprites[1] = ft_strdup(PLAYER_RIGHT_MV2);
	game->p1.right_sprites[2] = ft_strdup(PLAYER_RIGHT_MV3);
	game->p1.pl_ballom = ft_strdup(PLAYER_BALLOM);
}

void	put_player(t_game *game, int sprite_index)
{
	char	*current_sprite;
	int		x;
	int		y;

	x = game->p1.p1_p.x;
	y = game->p1.p1_p.y;
	if (game->p1.alive)
	{
		if (sprite_index < 0 || sprite_index >= 3)
			sprite_index = 0;
		if (game->p1.mv_dir == DIR_UP)
			current_sprite = game->p1.back_sprites[sprite_index];
		else if (game->p1.mv_dir == DIR_DOWN)
			current_sprite = game->p1.front_sprites[sprite_index];
		else if (game->p1.mv_dir == DIR_LEFT)
			current_sprite = game->p1.left_sprites[sprite_index];
		else if (game->p1.mv_dir == DIR_RIGHT)
			current_sprite = game->p1.right_sprites[sprite_index];
		else
			current_sprite = PLAYER_FRONT_STAND;
	}
	else
		current_sprite = PDEAD;
	game->p1.p1 = create_sprite(game, current_sprite);
	create_character(game->p1.p1, game, x, y);
	if (game->p1.p1)
		destroy_sprite(&game->p1.p1, game->mlx);
}
