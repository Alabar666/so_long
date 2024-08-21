/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:29 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/21 20:54:59 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_exit(t_game *game)
{
	game->ext.ex_p.x = 0;
	game->ext.ex_p.y = 0;
	game->ext.ex1 = NULL;
	game->ext.bl = NULL;
	game->ext.current_sprite = 0;
	game->ext.exit_sprites[0] = ft_strdup(EXIT_FRONT);
	game->ext.exit_sprites[1] = ft_strdup(EXIT_BACK);
	game->ext.exit_sprites[2] = ft_strdup(EXIT_LEFT);
	game->ext.exit_sprites[3] = ft_strdup(EXIT_RIGHT);
	game->ext.exit_ballom[0] = ft_strdup(EXIT_BHELP);
	game->ext.exit_ballom[1] = ft_strdup(EXIT_BCRY);
	game->ext.exit_ballom[2] = ft_strdup(EXIT_BFEAR);
	game->ext.exit_ballom[3] = ft_strdup(EXIT_BSAD);
}

void	put_exit(t_game *game)
{
	char		*current_exit;
	char		*current_ballom;
	static int	frame_counter;

	current_exit = game->ext.exit_sprites[(frame_counter / 120) % 4];
	if (frame_counter % 180 < 60)
		current_ballom = game->ext.exit_ballom[(frame_counter / 180) % 4];
	else
		current_ballom = NULL;
	game->ext.ex1 = create_sprite(game, current_exit);
	create_character(game->ext.ex1, game, game->ext.ex_p.x, game->ext.ex_p.y);
	if (game->ext.ex1)
		destroy_sprite(&game->ext.ex1, game->mlx);
	if (current_ballom)
	{
		game->ext.bl = create_sprite(game, current_ballom);
		create_character(game->ext.bl, game, game->ext.ex_p.x, game->ext.ex_p.y
			- 40);
		if (game->ext.bl)
			destroy_sprite(&game->ext.bl, game->mlx);		
	}
	frame_counter++;
	if (frame_counter > 720)
		frame_counter = 0;	
}
