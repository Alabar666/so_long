/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:20:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 19:15:07 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_pressed(int key, t_game *game)
{
	if (key == ESC && !game->is_paused)
	{
		gameover(game);
		return (0);
	}
	if (game->battle.is_running)
		return (handle_battle_keys(key, game));
	else
		return (handle_player_movement(key, game));
}

int	handle_player_movement(int key, t_game *game)
{
	if (game->p1.is_moving || !game->p1.alive)
		return (0);
	else if (key == KEY_W || key == UP)
	{
		if (game->map.map[(game->p1.p1_p.y / SZ) - 1][game->p1.p1_p.x
			/ SZ].type != '1')
			return (game->p1.mv_dir = DIR_UP, move_player(game, 0, -1), 0);
	}
	else if (key == KEY_S || key == DOWN)
	{
		if (game->map.map[(game->p1.p1_p.y / SZ) + 1][game->p1.p1_p.x
			/ SZ].type != '1')
			return (game->p1.mv_dir = DIR_DOWN, move_player(game, 0, +1), 0);
	}
	else if (key == KEY_A || key == LEFT)
	{
		if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ)
			- 1].type != '1')
			return (game->p1.mv_dir = DIR_LEFT, move_player(game, -1, 0), 0);
	}
	else if (key == KEY_D || key == RIGHT)
		if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ)
			+ 1].type != '1')
			return (game->p1.mv_dir = DIR_RIGHT, move_player(game, 1, 0), 0);
	return (0);
}

int	handle_battle_keys(int key, t_game *game)
{
	if (key == ENTER)
	{
		if (game->run_selected)
		{
			game->message_display_duration = 0;
			while (game->message_display_duration++ < 700000)
			{
				mlx_string_put(game->mlx, game->win, (game->world->width - 200)
					/ 2, (game->world->height - 50) / 2, 0xFFFF00,
					"The Goblin will not allow you to escape.");
			}
			return (0);
		}
		else
		{
			game->wait_input = 0;
			close_battle(game);
			return (0);
		}
	}
	return (battle_keys(key, game), 0);
}

void	move_player(t_game *game, int dx, int dy)
{
	t_pos	old_pos;
	t_pos	new_pos;

	if (game->p1.is_moving)
		return ;
	old_pos.x = game->p1.p1_p.x;
	old_pos.y = game->p1.p1_p.y;
	game->p1.dx = dx;
	game->p1.dy = dy;
	game->p1.steps_remaining = 10;
	game->p1.step_size = 4;
	game->p1.update_interval = 1000 / 60;
	new_pos.x = game->p1.p1_p.x + dx * 20 * 2;
	new_pos.y = game->p1.p1_p.y + dy * 20 * 2;
	game->p1.dest_p = new_pos;
	game->p1.last_update_time = clock();
	game->p1.accumulated_time = 0;
	game->p1.current_sprite = 0;
	game->p1.is_moving = 1;
	game->p1.moves++;
	ft_printf("Moves amount: %i\n", game->p1.moves);
	put_moves(game);
	check_position(game, game->p1.dest_p.x, game->p1.dest_p.y);
	update_map_tiles(game, old_pos, new_pos, 'P');
	check_for_overlap(game);
}

void	update_player_position(t_game *game)
{
	int		elapsed_time;
	int		time_per_step;
	clock_t	current_time;

	current_time = clock();
	elapsed_time = (current_time - game->p1.last_update_time) * 1000
		/ CLOCKS_PER_SEC;
	game->p1.accumulated_time += elapsed_time;
	time_per_step = game->p1.update_interval;
	while (game->p1.accumulated_time >= time_per_step
		&& game->p1.steps_remaining > 0)
	{
		game->p1.p1_p.x += game->p1.dx * game->p1.step_size;
		game->p1.p1_p.y += game->p1.dy * game->p1.step_size;
		game->p1.steps_remaining--;
		game->p1.current_sprite = (game->p1.current_sprite + 1) % 3;
		game->p1.accumulated_time -= time_per_step;
	}
	if (game->p1.steps_remaining == 0)
	{
		game->p1.is_moving = 0;
		game->p1.current_sprite = 0;
	}
	game->p1.last_update_time = current_time;
	check_for_overlap(game);
}
