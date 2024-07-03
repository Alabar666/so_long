/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:50 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/03 21:10:21 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_file_ext(char *file)
{
    size_t len;
    
    len = ft_strlen(file);
    if(ft_strncmp(file + len - 4, ".ber", 4))
        return(TRUE);
    return(FALSE);
}

int map_max_size_check(t_game *game,t_map *map)
{
    int screen_width;
    int screen_height;

    if(mlx_get_screen_size(game->mlx, &screen_width, &screen_height) != 0)
    {
        printf("Error\nFailed to get screen size.\n");
        return (0);
    }
    if(map->width > screen_height || map->height > screen_height)
    {
        pritf("Error\nMap size exceeds screen dimensions.\n");
        return (0);
    }
    return (1);   
}

int check_wall(t_map map)
{
    







    
}
