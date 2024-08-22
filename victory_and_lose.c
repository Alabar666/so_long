/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory_and_lose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:17:37 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/22 22:05:45 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_end_screen(t_game *game)
{
	if (game->end_img && game->show_end_screen)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->end_img->img, 0, 0);
		mlx_do_sync(game->mlx);
	}
}

void	end_game(t_game *game)
{
	game->show_end_screen = 1;
	create_end_screen(game);
	animate_end_screen(game);
}

void	resize_end(t_game *game, t_sprite *resized_end, char *image_path)
{
	t_sprite		*temp;
	t_pos			pos;
	t_pos			src_pos;
	unsigned int	color;
	t_pos_double	scale;

	temp = create_sprite(game, image_path);
	scale.x = (double)game->map.width / resized_end->width;
	scale.y = (double)game->map.height / resized_end->height;
	pos.y = -1;
	while (++pos.y < game->map.height)
	{
		pos.x = -1;
		while (++pos.x < game->map.width)
		{
			src_pos.x = (int)(pos.x / scale.x);
			src_pos.y = (int)(pos.y / scale.y);
			color = get_color_in_pixel(temp, src_pos.x, src_pos.y);
			put_pixel(resized_end, pos.x, pos.y, color);
		}
	}
	mlx_destroy_image(game->mlx, temp->img);
	free(temp);
	resized_end->width = game->map.width;
	resized_end->height = game->map.height;
}

void	animate_end_screen(t_game *game)
{
	char	*images[6];
	int		max_frames;
	int		frame;

	max_frames = 6;
	frame = 0;
	initialize_end_images(images);
	while (frame < max_frames)
	{
		if (game->end_img)
		{
			mlx_destroy_image(game->mlx, game->end_img->img);
			free(game->end_img);
			game->end_img = NULL;
		}
		game->end_img = create_sprite(game, images[frame]);
		resize_end(game, game->end_img, images[frame]);
		render_end_screen(game);
		if (game->end_img)
		destroy_sprite(&game->end_img, game->mlx);
		usleep(150000);
		frame++;
	}
}

void	create_end_screen(t_game *game)
{
	char	*images[6];

	initialize_end_images(images);
	if (game->end_img)
	{
		mlx_destroy_image(game->mlx, game->end_img->img);
		free(game->end_img);
		game->end_img = NULL;
	}
	game->end_img = create_sprite(game, images[0]);
	resize_end(game, game->end_img, images[0]);
	render_end_screen(game);
}
