/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/08 21:03:07 by hluiz-ma         ###   ########.fr       */
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

void free_map(t_game *game)
{
    int i;
    
    i = 0;
    while(i < game->map.height) 
    {
        free(game->map.map[i++]);
    }
    free(game->map.map);
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
void read_map(char *file, t_game *game)//map size rename
{    
    int fd;
    char *map; 
    char *mapfile;

    init_map(game, 1);
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
    mapfile = ft_calloc(sizeof(char), 10000);
    while(map)
    {   
        mapfile = ft_strcat(mapfile, map);
        free(map);
        map = get_next_line(fd); 
    }
    init_map(game, 0);
    game->map.map_data = mapfile;
    free(mapfile);
    close(fd);   
}


void map_start(char *file, t_game *game)
{
    read_map(file, game);//get size
    map_malloc(&game->map);
    fill_map(game);
    map_max_size_check(game, &game->map);
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
void map_malloc(t_map *map)
{
    int i;

    map->map = (t_tile **)ft_calloc(map->lines, sizeof(t_tile *));
    if(!map->map)
        exit(1);//fazer funcao para dar free
    i = 0;
    while(i < map->lines)
    {
        map->map[i]= (t_tile *)ft_calloc(map->colun, sizeof(t_tile *));
        if(!map->map[i++])
            exit(1);//fazer funcao para dar free
    }       
}
void fill_map(t_game *game)
{
    int x;
    int y;
    int i;
    char *mapd;

    mapd = game->map.map_data;
    y = 0;
    i = 0;
    while(mapd[i])
    {
        x = 0;
        //printf("Debug: Read line %s\n"), mapd; 
        while(mapd[i] && mapd[i] != '\n')
        {
            //printf("Map Y:%d X:%d line[x]:%c\n", y, x, mapd);
            game->map.map[y][x].type = mapd[i];
            x++;
            i++;
        }
        if (mapd[i] == '\n')
            i++;
        y++;
    }
}

char *ft_strcat(char *dest, const char* src)
{
    size_t i;
    size_t j;
    
    i = 0;
    j = 0;
    while(dest[i])
        i++;
    while(src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);   
}

