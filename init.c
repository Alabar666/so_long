/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:18:11 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/14 19:24:54 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_sprites(t_sprite sprites[4][3], void *mlx){
    
    sprites[0][0].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_STAND, &sprites[0][0].width, &sprites[0][0].height);
    sprites[0][1].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV1, &sprites[0][1].width, &sprites[0][1].height);
    sprites[0][2].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV2, &sprites[0][2].width, &sprites[0][2].height);

    sprites[1][0].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_STAND, &sprites[1][0].width, &sprites[1][0].height);
    sprites[1][1].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV1, &sprites[1][1].width, &sprites[1][1].height);
    sprites[1][2].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV2, &sprites[1][2].width, &sprites[1][2].height);

    sprites[2][0].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_STAND, &sprites[2][0].width, &sprites[2][0].height);
    sprites[2][1].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV1, &sprites[2][1].width, &sprites[2][1].height);
    sprites[2][2].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV2, &sprites[2][2].width, &sprites[2][2].height);

    sprites[3][0].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_STAND, &sprites[3][0].width, &sprites[3][0].height);
    sprites[3][1].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV1, &sprites[3][1].width, &sprites[3][1].height);
    sprites[3][2].img = mlx_xpm_file_to_image(mlx, PLAYER_FRONT_MV2, &sprites[3][2].width, &sprites[3][2].height);
    
}