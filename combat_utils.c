/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/18 14:31:01 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_battle(t_game *game)
{
	game->battle.btl_img = NULL;
	game->battle.gatk_path = ft_strdup(CGBLATK);
	game->battle.grun_path = ft_strdup(CGBLRUN);
	game->battle.eatk_path = ft_strdup(CENYATK);
	game->battle.erun_path = ft_strdup(CENYRUN);
	game->battle.is_running = 0;
	game->message_display_duration = 0;
	game->battle.enemy_type = '\0';
}
/*
void	create_battle(t_sprite *sprite, t_game *game)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	trans_color;

	trans_color = 0xFFC0CB;
	y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color)
			{
				put_pixel(game->battle.btl_img, x, y, color);
			}
		}
	}
}*/

void	create_battle_screen(t_game *game)
{
	t_sprite	*resized_combat;

	resized_combat = (t_sprite *)malloc(sizeof(t_sprite));
	resized_combat->width = game->map.width;
	resized_combat->height = game->map.height;
	resized_combat->img = mlx_new_image(game->mlx, resized_combat->width,
			resized_combat->height);
	resized_combat->addr = mlx_get_data_addr(resized_combat->img,
			&resized_combat->bits_per_pixel, &resized_combat->line_length,
			&resized_combat->endian);
	resize_combat(game, resized_combat);
	mlx_put_image_to_window(game->mlx, game->win, resized_combat->img, 0, 0);
	mlx_destroy_image(game->mlx, resized_combat->img);
	free(resized_combat);
}

void	resize_combat(t_game *game, t_sprite *resized_combat)
{
	int				x;
	int				y;
	unsigned int	color;
	double			src_x;
	double			src_y;

	y = -1;
	while (++y < resized_combat->height)
	{
		x = -1;
		while (++x < resized_combat->width)
		{
			src_x = (double)x * game->battle.btl_img->width
				/ resized_combat->width;
			src_y = (double)y * game->battle.btl_img->height
				/ resized_combat->height;
			color = get_color_in_pixel(game->battle.btl_img, (int)src_x,
					(int)src_y);
			put_pixel(resized_combat, x, y, color);
		}
	}
}

void	close_battle(t_game *game)
{
	destroy_sprite(&game->battle.btl_img, game->mlx);
	if (game->battle.gatk_path)
		free(game->battle.gatk_path);
	if (game->battle.grun_path)
		free(game->battle.grun_path);
	if (game->battle.eatk_path)
		free(game->battle.eatk_path);
	if (game->battle.erun_path)
		free(game->battle.erun_path);
	game->battle.gatk_path = NULL;
	game->battle.grun_path = NULL;
	game->battle.eatk_path = NULL;
	game->battle.erun_path = NULL;
	game->battle.is_running = 0;
	game->is_paused = 0;
}
