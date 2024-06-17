/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:20:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/17 20:45:16 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void key_pressed(int key, t_game *game){
    
    if (key == ESC)
    {
        gameover(game);
    }
    if (key == KEY_W || key == UP)
    {
        clean_img(game);
        game->plr.x--;
        game->map.map[game->plr.x][game->plr.y] = '0';
        draw_map(game);
        mlx_put_image_to_window(game->mlx, game->win, game->plr.plr, SZ*game->plr.y, SZ*(game->plr.x - 1));
    }
    if (key == KEY_S || key == DOWN)
    {
        clean_img(game);
        game->plr.x++;
        game->map.map[game->plr.x][game->plr.y] = '0';
        draw_map(game);
        mlx_put_image_to_window(game->mlx, game->win, game->plr.plr, SZ*game->plr.y, SZ*game->plr.x);
    }
    if (key == KEY_D || key == RIGHT)
    {
        clean_img(game);
        game->plr.y++;
        game->map.map[game->plr.x][game->plr.y] = '0';
        draw_map(game);
        mlx_put_image_to_window(game->mlx, game->win, game->plr.plr, SZ*game->plr.y, SZ*game->plr.x);
    }
    if (key == KEY_A || key == LEFT)
    {
        clean_img(game);
        game->plr.y--;
        game->map.map[game->plr.x][game->plr.y] = '0';
        draw_map(game);
        mlx_put_image_to_window(game->mlx, game->win, game->plr.plr, SZ*game->plr.y, SZ*game->plr.x);
    }
}