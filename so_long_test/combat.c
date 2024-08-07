/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/05 20:51:14 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
void load_combat_screen(t_game *game)
{
    int i, j, k;
    double angle, radius, max_radius;
    int center_x = game->map.width / 2;
    int center_y = game->map.height / 2;
    t_sprite *combat = create_sprite(game, COMBAT);

    max_radius = sqrt(center_x * center_x + center_y * center_y);
    for (k = 0; k < 100; k++) // Adjust the number of steps for a smoother transition
    {
        for (i = 0; i < game->map.height; i++)
        {
            for (j = 0; j < game->map.width; j++)
            {
                radius = sqrt((i - center_y) * (i - center_y) + (j - center_x) * (j - center_x));
                angle = atan2(i - center_y, j - center_x);
                int src_x = (int)(center_x + radius * cos(angle + M_PI * 2 * k / 100));
                int src_y = (int)(center_y + radius * sin(angle + M_PI * 2 * k / 100));
                
                if (src_x >= 0 && src_x < game->map.width && src_y >= 0 && src_y < game->map.height)
                    game->buffer[i][j] = battle_image->data[src_y * battle_image->width + src_x];
            }
        }
        mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);
        usleep(10000); // Adjust the delay for smoother transition
    }
}*/
/**/
void start_battle(t_game *game)
{
    game->is_paused = 1;
    open_battle_window(game);
    game->is_paused = 0;
}








