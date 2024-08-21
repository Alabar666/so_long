/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:43:53 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/21 21:17:35 by hluiz-ma         ###   ########.fr       */
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
		destroy_sprite(&game->p1.bl, game->mlx);
	}
	mlx_string_put(game->mlx, game->win, text_x, text_y, 0xFFFF00, move_str);
	free(move_str);
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
		game->p1.p1 = create_sprite(game, PDEAD);
		destroy_sprite(&game->p1.p1, game->mlx);
		game->p1.alive = 0;
		game->map.map[dy / SZ][dx / SZ].type = '0';
		if (!game->wait_input && !game->p1.alive)
		{
			ft_printf("You are dead!\n");
		}
	}
	if (game->map.goblin == 0 && enemy_type == 'E')
	{
		ft_printf("You saved the priestess!\n");
		end_game(game);
	}
}

void	check_for_overlap(t_game *game)
{
	int player_x;
	int player_y;
	t_goblin *cur_gbl;
	t_enemy *cur_eny;

	player_x = game->p1.p1_p.x;
	player_y = game->p1.p1_p.y;
	cur_gbl = game->gbl;
	cur_eny = game->eny;
	while (cur_gbl != NULL)
	{
		if (cur_gbl->gbl_p.x == player_x && cur_gbl->gbl_p.y == player_y)
		{
			handle_goblins(game, player_x, player_y);
			break ;
		}
		cur_gbl = cur_gbl->next;
	}
	while (cur_eny != NULL)
	{
		if (cur_eny->eny_p.x == player_x && cur_eny->eny_p.y == player_y)
		{
			handle_enemies_and_victory(game, player_x, player_y);
			break ;
		}
		cur_eny = cur_eny->next;
	}
}
