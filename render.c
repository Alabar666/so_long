/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:59:35 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 20:07:18 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(void *param)
{
	t_game			*game;
	t_goblin		*cur_gbl;
	t_enemy			*cur_eny;
	static clock_t	last_time = 0;
	clock_t			current_time;
	float			delta_time;

	game = (t_game *)param;
	current_time = clock();
	delta_time = (float)(current_time - last_time) / CLOCKS_PER_SEC;
	if (delta_time < 1.0f / 60.0f || game->is_paused)
		return (0);
	else
	{
		game->global_timer += delta_time;
		update_player_position(game);
		cur_gbl = game->gbl;
		if (game->p1.alive)
		{
			while (cur_gbl != NULL)
			{
				update_goblin_position(cur_gbl);
				cur_gbl = cur_gbl->next;
			}
			if (difftime(time(NULL), game->lst_gbl_upt) >= 2.0)
			{
				move_rand_goblins(game);
				game->lst_gbl_upt = time(NULL);
			}
			cur_eny = game->eny;
			while (cur_eny != NULL)
			{
				update_enemy_position(cur_eny);
				cur_eny = cur_eny->next;
			}
			if (difftime(time(NULL), game->lst_eny_upt) >= 1.5)
			{
				move_rand_enemys(game);
				game->lst_eny_upt = time(NULL);
			}
		}
		render_game(game);
		last_time = current_time;
	}
	return (0);
}

void	render_game(t_game *game)
{
	t_goblin	*current_goblin;
	t_enemy		*current_enemy;

	put_map(game);
	current_goblin = game->gbl;
	while (current_goblin != NULL)
	{
		put_goblin(game, current_goblin, current_goblin->current_sprite);
		current_goblin = current_goblin->next;
	}
	current_enemy = game->eny;
	while (current_enemy != NULL)
	{
		put_enemy(game, current_enemy, current_enemy->current_sprite);
		current_enemy = current_enemy->next;
	}
	if (game->p1.alive)
	{
		update_goblin_sprite_randomly(game);
		update_enemy_sprite_randomly(game);
	}
	put_exit(game);
	put_player(game, game->p1.current_sprite);
	put_moves(game);
	mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);
	if (game->p1.moves != 0)
		put_moves(game);
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

void	put_pixel(t_sprite *sprite, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
	{
		ft_printf("Sprite: %p\n", sprite);
		ft_printf("Error: Attempt to draw outside the image bounds (%d, %d)\n",
			x, y);
		return ;
	}
	dst = sprite->addr + (y * sprite->line_length + x * (sprite->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y)
{
	unsigned int color;

	color = *(unsigned int *)(sprite->addr + (y * sprite->line_length + x
				* (sprite->bits_per_pixel / 8)));
	return (color);
}