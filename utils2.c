/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:17:32 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 19:17:35 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_dead(t_game *game)
{
	char		*current_dead_text;
	static int	frame_counter;
	t_sprite	*temp;

	if ((frame_counter / 60) % 2 == 0)
	{
		current_dead_text = LOSE1;
	}
	else
	{
		current_dead_text = LOSE2;
	}
	temp = create_sprite(game, current_dead_text);
	resize_end_text(game->world, temp);
	destroy_sprite(&temp, game->mlx);
	frame_counter++;
	if (frame_counter >= 120)
	{
		frame_counter = 0;
	}
}

void	resize_end_text(t_sprite *dest, t_sprite *src)
{
	unsigned int	color;
	double			scale_x;
	double			scale_y;
	t_pos			pos;
	t_pos			src_pos;

	scale_x = (double)src->width / dest->width;
	scale_y = (double)src->height / dest->height;
	pos.y = -1;
	while (++pos.y < dest->height)
	{
		pos.x = -1;
		while (++pos.x < dest->width)
		{
			src_pos.x = (int)(pos.x * scale_x);
			src_pos.y = (int)(pos.y * scale_y);
			color = get_color_in_pixel(src, src_pos.x, src_pos.y);
			if (color != 0xFFC0CB)
			{
				put_pixel(dest, pos.x, pos.y, color);
			}
		}
	}
}

void	initialize_end_images(char *images[])
{
	images[0] = VICTORY1;
	images[1] = VICTORY2;
	images[2] = VICTORY3;
	images[3] = VICTORY4;
	images[4] = VICTORY5;
	images[5] = VICTORY6;
}
