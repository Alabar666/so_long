/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/03 21:50:50 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_game *game, int is_init)
{   
    if(is_init)
    {
      	game->map.map = NULL;
	    game->map.colun = 0;
	    game->map.lines = 0;
	    game->map.width = 0;
	    game->map.height = 0;
        game->map.exit = 0;
        game->map.enemy = 0;
        game->map.goblin = 0;
        game->map.player = 0;  
    }
    else
    {
        game->map.width = game->map.lines * SZ;
        game->map.height = game->map.colun * SZ;        
    }
        

}
int		count_lines(char *file)
{
	int		count;
	char	*str;
	int		fd;

	count = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}
void read_map(char *file, t_game *game)
{    
    int fd;
    char *map; 

    init_map(game, 0);
    fd = open(file, O_RDONLY);
    if(fd < 0){
        printf("Error opening map file %s\n", file);
        exit(EXIT_FAILURE);
    }
    if(!check_file_ext(file))
    {
        printf("Error map extension %s\n", file);
        exit(EXIT_FAILURE);
    }
    game->map.lines = count_lines(file);
    map = get_next_line(fd);
    game->map.colun = ft_strlen(map) - 1;
    while(map)
    {   
        free(map);
        map = get_next_line(fd); 
    }
    close(fd);   
}
//if (ft_strlen(m.filedata) != m.grid_x * m.grid_y + m.grid_y - 1)
//		error_game(data, ERROR_MAP_INVALID, "map is not rect.");
//if (m.item == 0 || m.player == 0 || m.exit != 1)
//    error_game(data, ERROR_MAP_INVALID, "map not meet minimun requirement");

void map_start(char * file, t_game *game)
{
    read_map(file, game);
    game->mlx = mlx_init();
	if (!game->mlx)
    {
        fprintf(stderr, "Error\nFailed to initialize mlx\n");
        exit(1);
    }
    game->win = mlx_new_window(game->mlx, SZ*game->map.colun, SZ*game->map.lines, "The Slayer");
	if (!game->win)
    {
        fprintf(stderr, "Error\nFailed to create window\n");
        exit(1);
    }
}
