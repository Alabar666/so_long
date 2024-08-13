/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:43:53 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/13 20:40:12 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_moves(t_game *game)
{
	char	*move_str;
	int		balloon_x;
	int		balloon_y;
	int		text_x;
	int		text_y;

	move_str = ft_itoa(game->p1.moves);
	balloon_x = game->p1.p1_p.x + 40;
	balloon_y = game->p1.p1_p.y - 40;
	text_x = balloon_x + 16;
	text_y = balloon_y + 19;
	if (game->p1.moves != 0)
	{
		game->p1.bl = create_sprite(game, game->p1.pl_ballom);
		create_character(game->p1.bl, game, balloon_x, balloon_y);
	}
	mlx_string_put(game->mlx, game->win, text_x, text_y, 0xFFFF00, move_str);
	free(move_str);
}

void	update_map_tiles(t_game *game, t_pos old_pos, t_pos new_pos, char type)
{
	int	map_old_x;
	int	map_old_y;
	int	map_new_x;
	int	map_new_y;

	map_old_x = old_pos.x / SZ;
	map_old_y = old_pos.y / SZ;
	map_new_x = new_pos.x / SZ;
	map_new_y = new_pos.y / SZ;
	if (game->map.map[map_new_y][map_new_x].type == '0')
	{
		game->map.map[map_old_y][map_old_x].type = '0';
		game->map.map[map_new_y][map_new_x].type = type;
	}
}

void	check_position(t_game *game, int dx, int dy)
{
	if (dx < 0 || dx >= game->map.width || dy < 0 || dy >= game->map.height)
		return ;
	handle_goblins(game, dx, dy);
	handle_enemies_and_victory(game, dx, dy);
}

void	handle_goblins(t_game *game, int dx, int dy)
{
	t_goblin	*cur_gbl;
	char		enemy_type;

	cur_gbl = game->gbl;
	enemy_type = game->map.map[dy / SZ][dx / SZ].type;
	if (enemy_type != 'C' && enemy_type != 'M')
		return ;
	while (cur_gbl != NULL)
	{
		if (cur_gbl->gbl_p.x == dx && cur_gbl->gbl_p.y == dy
			&& cur_gbl->is_alive)
		{
			cur_gbl->is_alive = 0;
			game->map.map[dy / SZ][dx / SZ].type = 'B';
			game->map.goblin--;
			start_battle(game, enemy_type);
			break ;
		}
		cur_gbl = cur_gbl->next;
	}
}

void	handle_enemies_and_victory(t_game *game, int dx, int dy)
{
	char	enemy_type;

	enemy_type = game->map.map[dy / SZ][dx / SZ].type;
	if (enemy_type == 'M')
	{
		start_battle(game, enemy_type);
		ft_printf("You are dead!\n");
		game->p1.p1 = create_sprite(game, PDEAD);
		game->p1.alive = 0;
		if (!game->wait_input && !game->p1.alive)
		{
			usleep(700000);
			gameover(game);
		}
	}
	if (game->map.goblin == 0 && enemy_type == 'E')
	{
		ft_printf("You saved the priestess!\n");
		usleep(700000);
		gameover(game);
	}
}
