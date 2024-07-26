/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:29 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/25 20:16:04 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_exit(t_game *game)
{
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
/*
void    create_exit(t_sprite *sprite, t_game *game, int posx, int posy)
{
    int x;
    int y;
    unsigned int color;
	unsigned int trans_color = 0xFFC0CB;

    y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color){
//                printf("Drawing pixel at (%d, %d) with color %x\n",
//                       posx + x, posy + y, color);
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
	}  
}*/
/*
void    create_ballom(t_sprite *sprite, t_game *game, int posx, int posy)
{
    int x;
    int y;
    unsigned int color;
	unsigned int trans_color = 0xFFC0CB;

    y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color){
//                printf("Drawing pixel at (%d, %d) with color %x\n",
//                       posx + x, posy + y, color);
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
	}  
}*/

void	put_exit(t_game *game, int moves)
{
    char *current_exit;
    char *current_ballom;

    current_exit = NULL;
    current_ballom = NULL;
    if(moves % 2 == 0)
        current_exit = game->ext.exit_sprites[(moves / 2) % 4];
    else
        current_exit = game->ext.exit_sprites[0];

    if(moves >= 3 && (moves % 4 == 3 || moves % 4 == 0))
        current_ballom = game->ext.exit_ballom[(moves / 2) % 4];
    else
        current_ballom = NULL;

    game->ext.ex1 = create_sprite(game, current_exit);
    create_character(game->ext.ex1, game, game->ext.ex_p.x, game->ext.ex_p.y);
    if(current_ballom)
    {
        game->ext.bl = create_sprite(game, current_ballom);
        create_character(game->ext.bl, game, game->ext.ex_p.x, game->ext.ex_p.y - 40);
    }
}
