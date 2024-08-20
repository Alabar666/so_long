/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:14:40 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/20 19:50:47 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_start(char *file, t_game *game)
{
	//init_map(game);
	read_map(file, game);
	game->map.width = game->map.colun * SZ;
	game->map.height = game->map.lines * SZ;
	map_malloc(&game->map);
	fill_map(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		gameover(game);
	}
	map_checks(game);
	game->win = mlx_new_window(game->mlx, game->map.width, game->map.height,
			"The Slayer");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		gameover(game);
	}
}

void	init_map(t_game *game)
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
	game->map.start_p1_p = (t_pos){0, 0};
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
