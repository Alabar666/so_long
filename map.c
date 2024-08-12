/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 20:21:55 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_start(char *file, t_game *game)
{
	init_map(game, 1);
	read_map(file, game);
	init_map(game, 0);
	map_malloc(&game->map);
	fill_map(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		return;
	}
	map_checks(game);
	game->win = mlx_new_window(game->mlx, SZ * game->map.colun, SZ
			* game->map.lines, "The Slayer");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		return;
	}
}
void	init_map(t_game *game, int is_init)
{
	if (is_init)
	{
		game->map.map = NULL;
		game->map.map_data = NULL;
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
		game->map.width = game->map.colun * SZ;
		game->map.height = game->map.lines * SZ;
	}
}

int	count_lines(char *file)
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
void	read_map(char *file, t_game *game)
{
	int		fd;
	char	*map;
	char	*mapfile;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening map file %s\n", file);
		return;
	}
	if (!check_file_ext(file))
	{
		ft_printf("Error map extension %s\n", file);
		game_error(fd, &game->map, MAP_ERROR);
	}
	game->map.lines = count_lines(file);
	map = get_next_line(fd);
	game->map.colun = ft_strlen(map) - 1;
	mapfile = ft_calloc(sizeof(char), 10000);
	if (!mapfile)
	{
		game_error(fd, &game->map, MAP_ERROR);
	}
	mapfile[0] = '\0';
	while (map)
	{
		mapfile = ft_strcat(mapfile, map);
		free(map);
		map = get_next_line(fd);
	}
	game->map.map_data = ft_strdup(mapfile);
	free(mapfile);
	close(fd);
}

void	map_malloc(t_map *map)
{
	int	i;

	i = 0;
	map->map = (t_tile **)ft_calloc(map->lines + 1, sizeof(t_tile *) * SZ);
	if (!map->map)
		game_error(0, map, MAP_ERROR);
	while (i < map->lines)
	{
		map->map[i] = (t_tile *)ft_calloc(map->colun + 1, sizeof(t_tile *)
				* SZ);
		if (!map->map[i++])
			game_error(0, map, MAP_ERROR);
	}
}
t_tile	new_tile(char type, int x, int y)
{
	t_tile	tile;

	tile.type = type;
	tile.pos.x = x;
	tile.pos.y = y;
	return (tile);
}

void	fill_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	char	*mapd;

	mapd = game->map.map_data;
	y = 0;
	i = 0;
	while (mapd[i])
	{
		x = 0;
		while (mapd[i] && mapd[i] != '\n')
		{
			check_type(game, mapd[i], x, y);
			game->map.map[y][x] = new_tile(mapd[i], x * SZ, y * SZ);
			game->map.map[y][x].sprt_path = NULL;
			x++;
			i++;
		}
		if (mapd[i] == '\n')
			i++;
		y++;
	}
}
void	check_type(t_game *game, char type, int x, int y)
{
	if (type)
	{
		if (type == 'P')
		{
			game->map.player++;
			game->map.start_p1_p.x = x * SZ;
			game->map.start_p1_p.y = y * SZ;
		}
		else if (type == 'E')
		{
			game->map.exit++;
			game->ext.ex_p.x = x * SZ;
			game->ext.ex_p.y = y * SZ;
		}
		else if (type == 'C')
		{
			game->map.goblin++;
			add_goblin_to_list(game, x * SZ, y * SZ);
		}
		else if (type == 'M')
		{
			game->map.enemy++;
			add_enemy_to_list(game, x * SZ, y * SZ);
		}
	}
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
void	put_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	sprite = NULL;
	y = -1;
	while (++y < game->map.lines)
	{
		x = -1;
		while (++x < game->map.colun)
		{
			sprite = create_sprite(game, game->map.map[y][x].sprt_path);
			create_world(sprite, game, x, y);
			mlx_destroy_image(game->mlx, sprite->img);
			free(sprite);
		}
	}
}