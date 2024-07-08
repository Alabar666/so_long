/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:06:50 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/05 19:22:31 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_file_ext(char *file)
{
    size_t len;
    char *exten;
    
    len = ft_strlen(file);
    if(len < 4)
        return(0);
    exten = file + (len - 4);
    return(!ft_strncmp(".ber", exten, 4));
}

int map_max_size_check(t_game *game,t_map *map)
{
    int screen_width;
    int screen_height;
   
    if (game == NULL) {
        printf("Error: Invalid game pointer.\n");
        return 0;
    }

    if (map == NULL) {
        printf("Error: Invalid map pointer.\n");
        return 0;
    }

    if (game->mlx == NULL) {
        printf("Error: Invalid game->mlx pointer.\n");
        return 0;
    }


    if(mlx_get_screen_size(game->mlx, &screen_width, &screen_height) != 0)
    {
        printf("Error\nFailed to get screen size.\n");
        return (0);
    }
    printf("Debug: Screen width: %d, Screen height: %d\n", screen_width, screen_height);
    printf("Debug: Map width: %d, Map height: %d\n", map->width, map->height);
    if(map->width > screen_height || map->height > screen_height)
    {
        printf("Error\nMap size exceeds screen dimensions.\n");
        return (0);
    }
    return (1);   
}
//if (ft_strlen(m.filedata) != m.grid_x * m.grid_y + m.grid_y - 1)
//		error_game(data, ERROR_MAP_INVALID, "map is not rect.");
//if (m.item == 0 || m.player == 0 || m.exit != 1)
//    error_game(data, ERROR_MAP_INVALID, "map not meet minimun requirement");
int is_map_rectangular(char **map)
{
    int width;
    int i;
    
    if(!map || !map[0])
        return(0);
    width = strlen(map[0]);
    i = -1;
    while(map[++i])
    {
        if((int)ft_strlen(map[i]) != width)
            return (0);
    }
    return (1);
}

int check_wall(t_map map)
{
    int i;
    int x;
    int y;
    
    i = 0;
    y = 0;
    while(map.map[i])
    {
        x = 0;
        while(map.map[i])
        {
            if((x == 0 || x == map.lines - 1) && map.map[y][x].type != '1')
                return(0);
            if((y == 0 || y == map.colun - 1) && map.map[y][x].type != '1')
                return(0);
            i++;
            x++;        
        }
        i++;
        y++;     
    }
    return (1);    
}
