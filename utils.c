/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:31:08 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 19:17:30 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(int directions[4][2])
{
	directions[0][0] = 0;
	directions[0][1] = -1;
	directions[1][0] = 0;
	directions[1][1] = 1;
	directions[2][0] = -1;
	directions[2][1] = 0;
	directions[3][0] = 1;
	directions[3][1] = 0;
}

void	init_game(t_game *game)
{
	if (game == NULL)
		return ;
	game->mlx = NULL;
	game->win = NULL;
	init_map(game);
	game->world = NULL;
	game->end_img = NULL;
	init_player(game);
	game->gbl = NULL;
	game->eny = NULL;
	init_exit(game);
	init_battle(game);
	game->lst_gbl_upt = time(NULL);
	game->lst_eny_upt = time(NULL);
	game->lst_exit_upt = time(NULL);
	game->global_timer = 0;
	game->sprite_index = 0;
	game->is_paused = 0;
	game->wait_input = 0;
	game->run_selected = 0;
	game->show_end_screen = 0;
	game->message_display_duration = 0;
}

void	init_list_enemy(t_game *game)
{
	game->eny = NULL;
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
	unsigned int	color;

	color = *(unsigned int *)(sprite->addr + (y * sprite->line_length + x
				* (sprite->bits_per_pixel / 8)));
	return (color);
}
