/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/25 20:31:18 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
void parse_map(char *file, t_game *game)
{    
    int fd;
    int i;
    char *map; 

    init_map(game);
    fd = open(file, O_RDONLY);
    if(fd < 0){
        printf("Error opening map file %s\n", file);
        exit(EXIT_FAILURE);
    }
    game->map.lines = count_lines(file);
    game->map.map = ft_calloc(sizeof(char *), game->map.lines);
    i = 0;
    while((map = get_next_line(fd)) != NULL)
    {   
        game->map.map[i] = ft_calloc(sizeof(char *), ft_strlen(map) + 1);
        game->map.map[i] = ft_strdup(map);
        free(map);   
        i++; 
    }
    game->map.colun = ft_strlen(game->map.map[0]) - 1;
    close(fd);   
}

void map_start(char * file, t_game *game)
{
    parse_map(file, game);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, SZ*game->map.colun, SZ*game->map.lines, "The Slayer");
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

    load_images(game);
	x = -1;
	while (game->map.map[++x])
	{
		y = -1;
		while (game->map.map[x][++y])
		{
            if(game->map.map[x][y] == '0')
			    mlx_put_image_to_window(game->mlx, game->win, game->map.floor, SZ*y, SZ*x);
            if(game->map.map[x][y] == '1')
			    mlx_put_image_to_window(game->mlx, game->win, game->map.wall, SZ*y, SZ*x);
            if(game->map.map[x][y] == 'P')
			    mlx_put_image_to_window(game->mlx, game->win, game->plr.plr, SZ*y, SZ*x);
            if(game->map.map[x][y] == 'E')
			    mlx_put_image_to_window(game->mlx, game->win, game->map.exit, SZ*y, SZ*x);
            if(game->map.map[x][y] == 'C')
			    mlx_put_image_to_window(game->mlx, game->win, game->gc.gc, SZ*y, SZ*x);
            if(game->map.map[x][y] == 'T')
			    mlx_put_image_to_window(game->mlx, game->win, game->ge.ge, SZ*y, SZ*x);
		}
	}
}
