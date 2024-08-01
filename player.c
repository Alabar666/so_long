/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:10:30 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/25 20:16:33 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_player(t_game *game)
{
    game->p1.p1_p.x = game->map.start_p1_p.x;   
    game->p1.p1_p.y = game->map.start_p1_p.y; 
    game->p1.alive = 1;
    game->p1.mv_dir = STAND;
    game->p1.face = STAND;
    game->p1.moves = 0;
    game->p1.current_sprite = 0;

	game->p1.front_sprites[0] = ft_strdup(PLAYER_FRONT_STAND);
    game->p1.front_sprites[1] = ft_strdup(PLAYER_FRONT_MV1);
    game->p1.front_sprites[2] = ft_strdup(PLAYER_FRONT_MV2);

    game->p1.back_sprites[0] = ft_strdup(PLAYER_BACK_MV1);
    game->p1.back_sprites[1] = ft_strdup(PLAYER_BACK_MV2);
    game->p1.back_sprites[2] = ft_strdup(PLAYER_BACK_MV3);

    game->p1.left_sprites[0] = ft_strdup(PLAYER_LEFT_MV1);
    game->p1.left_sprites[1] = ft_strdup(PLAYER_LEFT_MV2);
    game->p1.left_sprites[2] = ft_strdup(PLAYER_LEFT_MV3);

    game->p1.right_sprites[0] = ft_strdup(PLAYER_RIGHT_MV1);
    game->p1.right_sprites[1] = ft_strdup(PLAYER_RIGHT_MV2);
    game->p1.right_sprites[2] = ft_strdup(PLAYER_RIGHT_MV3);  
    
    game->p1.dx = 0;
    game->p1.dy = 0;
    game->p1.steps_remaining = 0;
    game->p1.step_size = 0;
    game->p1.update_interval = 1000 / 60;
    game->p1.last_update_time = clock();
    game->p1.accumulated_time = 0;

}
/*
void    create_player(t_sprite *sprite, t_game *game, int posx, int posy)
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
			if (color != trans_color)
            {
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
	}  
}*/

void	put_player(t_game *game, int sprite_index)
{
    char *current_sprite;
    int x = game->p1.p1_p.x;
    int y = game->p1.p1_p.y;

	x = game->p1.p1_p.x;
	y = game->p1.p1_p.y;

    if (game->p1.mv_dir == DIR_UP)
    {
        if(sprite_index < 3)
            current_sprite = game->p1.back_sprites[sprite_index];
        else
            current_sprite = game->p1.back_sprites[0];
    }    
    else if (game->p1.mv_dir == DIR_DOWN)
    {
        if(sprite_index < 3)
            current_sprite = game->p1.front_sprites[sprite_index];
        else
            current_sprite = game->p1.front_sprites[0];
    } 
    else if (game->p1.mv_dir == DIR_LEFT)
    {
        if(sprite_index < 3)
            current_sprite = game->p1.left_sprites[sprite_index];
        else
            current_sprite = game->p1.left_sprites[0];
    } 
    else if (game->p1.mv_dir == DIR_RIGHT)
    {
        if(sprite_index < 3)
            current_sprite = game->p1.right_sprites[sprite_index];
        else
            current_sprite = game->p1.right_sprites[0];
    } 
    else
        current_sprite = ft_strdup(PLAYER_FRONT_STAND);

    game->p1.p1 = create_sprite(game, current_sprite);
    create_character(game->p1.p1, game, x, y);
}
/*
void put_player(t_game *game, int sprite_index)
{
    char *current_sprite;
    int x = game->p1.p1_p.x;
    int y = game->p1.p1_p.y;

    if (game->p1.mv_dir == DIR_UP)
    {
        current_sprite = game->p1.back_sprites[sprite_index];
    }    
    else if (game->p1.mv_dir == DIR_DOWN)
    {
        current_sprite = game->p1.front_sprites[sprite_index];
    } 
    else if (game->p1.mv_dir == DIR_LEFT)
    {
        current_sprite = game->p1.left_sprites[sprite_index];
    } 
    else if (game->p1.mv_dir == DIR_RIGHT)
    {
        current_sprite = game->p1.right_sprites[sprite_index];
    } 
    else
    {
        current_sprite = ft_strdup(PLAYER_FRONT_STAND);
    }

    game->p1.p1 = create_sprite(game, current_sprite);
    create_character(game->p1.p1, game, x, y);
}*/