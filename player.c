/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:10:30 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/15 22:26:59 by hluiz-ma         ###   ########.fr       */
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
    game->p1.currect_sprite = 0;

	game->p1.front_sprites[0] = create_sprite(game, ft_strdup(PLAYER_FRONT_STAND));
    game->p1.front_sprites[1] = create_sprite(game, ft_strdup(PLAYER_FRONT_MV1));
    game->p1.front_sprites[2] = create_sprite(game, ft_strdup(PLAYER_FRONT_MV2));

    game->p1.back_sprites[0] = create_sprite(game, ft_strdup(PLAYER_BACK_MV1));
    game->p1.back_sprites[1] = create_sprite(game, ft_strdup(PLAYER_BACK_MV2));
    game->p1.back_sprites[2] = create_sprite(game, ft_strdup(PLAYER_BACK_MV3));

    game->p1.left_sprites[0] = create_sprite(game, ft_strdup(PLAYER_LEFT_MV1));
    game->p1.left_sprites[1] = create_sprite(game, ft_strdup(PLAYER_LEFT_MV2));
    game->p1.left_sprites[2] = create_sprite(game, ft_strdup(PLAYER_LEFT_MV3));

    game->p1.right_sprites[0] = create_sprite(game, ft_strdup(PLAYER_RIGHT_MV1));
    game->p1.right_sprites[1] = create_sprite(game, ft_strdup(PLAYER_RIGHT_MV2));
    game->p1.right_sprites[2] = create_sprite(game, ft_strdup(PLAYER_RIGHT_MV3));  
}

int	update_player_frame(t_game *game)
{
	static int frame_counter = 0;
	
	game->p1.currect_sprite = (frame_counter / 10) % 3;
	put_player_mov(game);
	
	mlx_put_image_to_window(game->mlx, game->win, game->world->img,
		0, 0);

	frame_counter++;	
    return (0);    
}

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
			if (color != trans_color){
                printf("Drawing pixel at (%d, %d) with color %x\n",
                       posx + x, posy + y, color);
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
	}  
}

void	put_player_mov(t_game *game)
{
    t_sprite *current_sprite;
    int x = game->p1.p1_p.x;
    int y = game->p1.p1_p.y;

	x = game->p1.p1_p.x;
	y = game->p1.p1_p.y;
    printf("Put player on map...\n");
    if (game->p1.mv_dir == DIR_UP)
        current_sprite = game->p1.back_sprites[game->p1.currect_sprite];
    else if (game->p1.mv_dir == DIR_DOWN)
        current_sprite = game->p1.front_sprites[game->p1.currect_sprite];
    else if (game->p1.mv_dir == DIR_LEFT)
        current_sprite = game->p1.left_sprites[game->p1.currect_sprite];
    else if (game->p1.mv_dir == DIR_RIGHT)
        current_sprite = game->p1.right_sprites[game->p1.currect_sprite];
    else
        current_sprite = game->p1.front_sprites[0];

    create_player(current_sprite, game, x, y);
    printf("Player placed successfully.\n"); // Mensagem de depuração
}
char	*get_player_path(t_game *game, char c)
{
	char	*path;
	int randv;

	randv = rand();
	path = NULL;
	if (c == 'P')
		path = ft_strdup(PLAYER_FRONT_STAND);		
	else if (c == 'E')
		path = ft_strdup(EXIT);	
	else if (c == 'C')
		path = ft_strdup(GOBLIN_FRONT_STAND);	
/*	else if (c == '0' || c == 'C' || c == 'E')
	{
		if(randv % 2 == 0)
			path = ft_strdup(FLOOR);
		else if(randv % 3 == 0)
			path = ft_strdup(FLOOR2);
		else
			path = ft_strdup(FLOOR3);		
	}*/
	if (!path)
    {
        fprintf(stderr, "Failed to allocate path for character: %c\n", c);
		gameover(game);
    }
	return (path);
}