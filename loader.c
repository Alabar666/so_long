/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:26:04 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/25 20:34:11 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*xpm_r(t_game *g, char *path, t_sprite *s)
{
	return (mlx_xpm_file_to_image(g->mlx, path, s->px_size, s->px_size));
}

void render_map(t_game *g, t_sprite *s)
{
    s->px_size = ft_calloc(1, sizeof(int));
    *s->px_size = SZ;
    s->floor =xpm_r(g, FLOOR, s);
    s->wall =xpm_r(g, WALL, s);

    free(s->px_size);      
}

void render_img(t_game *g, void *img_ptr, t_map *m)
{
    int x;
    int y;
    
    x = m->colun * SZ;
    y = m->lines * SZ;
    mlx_put_image_to_window(g->mlx, g->win, img_ptr, x, y);    
}