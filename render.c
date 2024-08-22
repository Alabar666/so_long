/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:59:35 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/22 20:16:18 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(t_game *game)
{
	static clock_t	last_time = 0;
	clock_t			current_time;
	float			delta_time;

	current_time = clock();
	delta_time = (float)(current_time - last_time) / CLOCKS_PER_SEC;
	if (delta_time >= 1.0f / 60.0f && !game->is_paused)
	{
		if (!game->show_end_screen)
		{
			update_game_elements(game, &last_time);
			render_game(game);
		}
		else
		{
			render_end_screen(game);
		}
	}
	return (0);
}

void	update_game_elements(t_game *game, clock_t *last_time)
{
	clock_t	current_time;
	float	delta_time;

	current_time = clock();
	delta_time = (float)(current_time - *last_time) / CLOCKS_PER_SEC;
	game->global_timer += delta_time;
	update_player_position(game);
	if (game->p1.alive)
	{
		update_positions(game);
		move_randomly(game);
		check_for_overlap(game);
	}
	*last_time = current_time;
}

void	update_positions(t_game *game)
{
	t_goblin	*cur_gbl;
	t_enemy		*cur_eny;

	cur_gbl = game->gbl;
	while (cur_gbl != NULL)
	{
		update_goblin_position(cur_gbl);
		cur_gbl = cur_gbl->next;
	}
	cur_eny = game->eny;
	while (cur_eny != NULL)
	{
		update_enemy_position(cur_eny);
		cur_eny = cur_eny->next;
	}
}

void	move_randomly(t_game *game)
{
	if (difftime(time(NULL), game->lst_gbl_upt) >= 2.0)
	{
		move_rand_goblins(game);
		game->lst_gbl_upt = time(NULL);
	}
	if (difftime(time(NULL), game->lst_eny_upt) >= 1.5)
	{
		move_rand_enemys(game);
		game->lst_eny_upt = time(NULL);
	}
}

void	create_world(t_sprite *sprite, t_game *game, int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	trans_color;

	trans_color = 0xFFC0CB;
	y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color)
			{
				put_pixel(game->world, posx * SZ + x, posy * SZ + y, color);
			}
		}
	}
}
