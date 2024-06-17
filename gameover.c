/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:49:26 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/17 19:54:51 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void clean_img(t_game *game)
{
    mlx_destroy_image(game->mlx, game->map.floor);
    mlx_destroy_image(game->mlx, game->map.wall);
    mlx_destroy_image(game->mlx, game->plr.plr);
    mlx_destroy_image(game->mlx, game->gc.gc);
    mlx_destroy_image(game->mlx, game->ge.ge);
    free(game->map.img);
}

void gameover(t_game *game)
{
    size_t i;
    
    i = 0;
    while(game->map.map[i])
        free(game->map.map[i++]);
    clean_img(game);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->map.map);
    free(game->mlx);
    exit(0);    
}
