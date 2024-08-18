/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:02:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/18 12:23:23 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_goblins_check(t_game *game, t_goblin *gbl, int dx, int dy)
{
	int	new_x;
	int	new_y;

	if (!gbl->is_alive)
		return (0);
	new_x = gbl->gbl_p.x + dx * SZ;
	new_y = gbl->gbl_p.y + dy * SZ;
	if (game->map.map[new_y / SZ][new_x / SZ].type == '1' || game->map.map[new_y
		/ SZ][new_x / SZ].type == 'C' || game->map.map[new_y / SZ][new_x
		/ SZ].type == 'E' || game->map.map[new_y / SZ][new_x / SZ].type == 'M')
		return (0);
	if (dx == 0 && dy == -1)
		gbl->mv_dir = DIR_UP;
	else if (dx == 0 && dy == 1)
		gbl->mv_dir = DIR_DOWN;
	else if (dx == -1 && dy == 0)
		gbl->mv_dir = DIR_LEFT;
	else if (dx == 1 && dy == 0)
		gbl->mv_dir = DIR_RIGHT;
	return (1);
}

void	move_goblin(t_game *game, t_goblin *gbl, int dx, int dy)
{
	t_pos	old_pos;
	t_pos	new_pos;

	if (gbl->is_moving)
		return ;
	old_pos.x = gbl->gbl_p.x;
	old_pos.y = gbl->gbl_p.y;
	gbl->dx = dx;
	gbl->dy = dy;
	gbl->steps_remaining = 10;
	gbl->step_size = 4;
	gbl->update_interval = 1000 / 60;
	new_pos.x = gbl->gbl_p.x + dx * 20 * 2;
	new_pos.y = gbl->gbl_p.y + dy * 20 * 2;
	gbl->dest_p = new_pos;
	gbl->last_update_time = clock();
	gbl->accumulated_time = 0;
	gbl->current_sprite = 0;
	gbl->is_moving = 1;
	update_map_tiles(game, old_pos, new_pos, 'C');
	check_for_overlap(game);
}

void	update_goblin_position(t_goblin *gbl)
{
	clock_t	current_time;
	int		elapsed_time;
	int		time_per_step;

	current_time = clock();
	elapsed_time = (current_time - gbl->last_update_time) * 1000
		/ CLOCKS_PER_SEC;
	gbl->accumulated_time += elapsed_time;
	time_per_step = gbl->update_interval;
	while (gbl->accumulated_time >= time_per_step && gbl->steps_remaining > 0)
	{
		gbl->gbl_p.x += gbl->dx * gbl->step_size;
		gbl->gbl_p.y += gbl->dy * gbl->step_size;
		gbl->steps_remaining--;
		gbl->current_sprite = (gbl->current_sprite + 1) % 3;
		gbl->accumulated_time -= time_per_step;
	}
	if (gbl->steps_remaining == 0)
	{
		gbl->is_moving = 0;
		gbl->current_sprite = 0;
	}
	gbl->last_update_time = current_time;
}

void	move_rand_goblins(t_game *game)
{
	t_goblin	*cur_gbl;
	int			directions[4][2];
	int			dir_index;
	int			dx;
	int			dy;

	cur_gbl = game->gbl;
	init_directions(directions);
	while (cur_gbl != NULL)
	{
		if (cur_gbl->is_alive && rand() % 6 == 0)
		{
			dir_index = rand() % 4;
			dx = directions[dir_index][0];
			dy = directions[dir_index][1];
			if (move_goblins_check(game, cur_gbl, dx, dy))
			{
				move_goblin(game, cur_gbl, dx, dy);
			}
		}
		cur_gbl = cur_gbl->next;
	}
}

void	update_goblin_sprite_randomly(t_game *game)
{
	t_goblin	*current_goblin;
	static int	frame_counter = 0;

	frame_counter++;
	if (frame_counter >= 180)
	{
		current_goblin = game->gbl;
		while (current_goblin != NULL)
		{
			if (rand() % 20)
			{
				current_goblin->mv_dir = rand() % 4;
				put_goblin(game, current_goblin,
					current_goblin->current_sprite);
			}
			current_goblin = current_goblin->next;
		}
		frame_counter = 0;
	}
}
