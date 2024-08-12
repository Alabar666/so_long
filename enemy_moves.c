/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 20:15:45 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_enemys_check(t_game *game, t_enemy *eny, int dx, int dy)
{
	int	new_x;
	int	new_y;

	if (!eny->is_alive)
		return (0);
	new_x = eny->eny_p.x + dx * SZ;
	new_y = eny->eny_p.y + dy * SZ;
	if (game->map.map[new_y / SZ][new_x / SZ].type == '1' || game->map.map[new_y
		/ SZ][new_x / SZ].type == 'C' || game->map.map[new_y / SZ][new_x
		/ SZ].type == 'E' || game->map.map[new_y / SZ][new_x / SZ].type == 'M')
		return (0);
	if (dx == 0 && dy == -1)
		eny->mv_dir = DIR_UP;
	else if (dx == 0 && dy == 1)
		eny->mv_dir = DIR_DOWN;
	else if (dx == -1 && dy == 0)
		eny->mv_dir = DIR_LEFT;
	else if (dx == 1 && dy == 0)
		eny->mv_dir = DIR_RIGHT;
	return (1);
}

void	move_enemy(t_game *game, t_enemy *eny, int dx, int dy)
{
	int	old_x;
	int	old_y;

	if (eny->is_moving)
		return ;
	old_x = eny->eny_p.x;
	old_y = eny->eny_p.y;
	eny->dx = dx;
	eny->dy = dy;
	eny->steps_remaining = 10;
	eny->step_size = 4;
	eny->update_interval = 1000 / 60;
	eny->dest_p.x = eny->eny_p.x + dx * 20 * 2;
	eny->dest_p.y = eny->eny_p.y + dy * 20 * 2;
	eny->last_update_time = clock();
	eny->accumulated_time = 0;
	eny->current_sprite = 0;
	eny->is_moving = 1;
	update_map_tiles(game, old_x, old_y, eny->dest_p.x, eny->dest_p.y, 'M');
}

void	update_enemy_position(t_enemy *eny)
{
	clock_t	current_time;
	int		elapsed_time;
	int		time_per_step;

	current_time = clock();
	elapsed_time = (current_time - eny->last_update_time) * 1000
		/ CLOCKS_PER_SEC;
	eny->accumulated_time += elapsed_time;
	time_per_step = eny->update_interval;
	while (eny->accumulated_time >= time_per_step && eny->steps_remaining > 0)
	{
		eny->eny_p.x += eny->dx * eny->step_size;
		eny->eny_p.y += eny->dy * eny->step_size;
		eny->steps_remaining--;
		eny->current_sprite = (eny->current_sprite + 1) % 3;
		eny->accumulated_time -= time_per_step;
	}
	if (eny->steps_remaining == 0)
	{
		eny->is_moving = 0;
		eny->current_sprite = 0;
	}
	eny->last_update_time = current_time;
}

void	move_rand_enemys(t_game *game)
{
	t_enemy	*cur_eny;
	int		directions[4][2];
	int		dir_index;
	int		dx;
	int		dy;

	cur_eny = game->eny;
	init_directions(directions);
	while (cur_eny != NULL)
	{
		if (cur_eny->is_alive && rand() % 2 == 0)
		{
			dir_index = rand() % 4;
			dx = directions[dir_index][0];
			dy = directions[dir_index][1];
			if (move_enemys_check(game, cur_eny, dx, dy))
			{
				move_enemy(game, cur_eny, dx, dy);
			}
		}
		cur_eny = cur_eny->next;
	}
}

void	update_enemy_sprite_randomly(t_game *game)
{
	t_enemy *current_enemy;
	static int frame_counter;
	frame_counter++;

	if (frame_counter >= 180)
	{
		current_enemy = game->eny;
		while (current_enemy != NULL)
		{
			if (rand() % 20)
			{
				current_enemy->mv_dir = rand() % 4;
				put_enemy(game, current_enemy, current_enemy->current_sprite);
			}
			current_enemy = current_enemy->next;
		}
		frame_counter = 0;
	}
}
