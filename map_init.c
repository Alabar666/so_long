
#include "so_long.h"

void	map_start(char *file, t_game *game)
{
	init_map(game);
	read_map(file, game);
	game->map.width = game->map.colun * SZ;
	game->map.height = game->map.lines * SZ;
	map_malloc(&game->map);
	fill_map(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		return ;
	}
	map_checks(game);
	game->win = mlx_new_window(game->mlx, SZ * game->map.colun, SZ
			* game->map.lines, "The Slayer");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		return ;
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
