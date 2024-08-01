/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:25:58 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/29 22:07:50 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int update_frame(void *param)
{
    t_game *game = (t_game *)param;
    static clock_t last_time = 0;
    clock_t current_time = clock();
    float delta_time = (float)(current_time - last_time) / CLOCKS_PER_SEC;
    
    if (delta_time < 1.0f / 60.0f) // Se o tempo desde o último frame for menor que 1/60 segundos, pular este frame
        return 0;

    game->global_timer += delta_time;

	update_player_position(game);

    // Atualizar os goblins aleatoriamente
    if (difftime(time(NULL), game->lst_gbl_upt) >= 1.0)
    {
        move_rand_goblins(game, game->gbl);
        game->lst_gbl_upt = time(NULL);
    }

    // Renderizar o jogo
    render_game(game);
	last_time = current_time;

    return 0;
} 

void render_game(t_game *game)
{
    // Renderizar o mapa
    put_map(game);
    put_exit(game);

    // Renderizar os goblins
    t_goblin *current_goblin = game->gbl;
    while (current_goblin != NULL)
    {
        put_goblin(game, current_goblin, 0);
        current_goblin = current_goblin->next;
    }
	update_goblin_sprite_randomly(game);
    // Renderizar o jogador
    put_player(game, game->p1.current_sprite);

    // Atualizar a janela
    mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);
}

/*
int	update_frame(t_game *game, int index)
{
    clock_t start, end;
	time_t current_time;
    long sleep_time;
	t_goblin *current_goblin = game->gbl;

    start = clock();	
	current_time = time(NULL);
	put_map(game);
	put_exit(game, game->p1.moves);

	if (difftime(current_time, game->lst_gbl_upt) >= 2.0)
    {
		while (current_goblin != NULL)
   		{
       		move_rand_goblins(game, current_goblin);
	//		update_goblin_sprite_randomly(current_goblin);
	        current_goblin = current_goblin->next;
		}
        game->lst_gbl_upt = current_time; // Atualize o tempo da última atualização
    }
//	update_all_goblins(game);
	put_player(game, index);
	mlx_put_image_to_window(game->mlx, game->win, game->world->img,
		0, 0);
	end = clock();
	sleep_time = FRAME_DURATION - ((end - start) * 1000000 / CLOCKS_PER_SEC);
    if (sleep_time > 0)
    {
        usleep(sleep_time);
    }
    return (0);    
}*/


t_sprite *create_sprite(t_game *game, char *sprite_path)
{
    t_sprite *sprite;

    sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
    if(!sprite)
    {
		return NULL;
 //       free(sprite_path);
 //       gameover(game);
    }
  //  printf("Loading sprite from path: %s\n", sprite_path); // Mensagem de depuração
    sprite->img = mlx_xpm_file_to_image(game->mlx, sprite_path, &sprite->width,&sprite->height);
    if(!sprite->img)
    {
        fprintf(stderr, "Failed to load image: %s\n", sprite_path); // Mensagem de erro
//        free(sprite);
 //       free(sprite_path);
//        gameover(game);
	return NULL;
    } 
    sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
    &sprite->line_length, &sprite->endian);
//    free(sprite_path);
 //   printf("Sprite loaded successfully: %s\n", sprite_path); // Mensagem de depuração
    return(sprite);  
}

void    create_world(t_sprite *sprite, t_game *game, int posx, int posy)
{
    int x;
    int y;
    unsigned int color;
	unsigned int trans_color = 0xFFC0CB;

    y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color){
               // printf("Drawing pixel at (%d, %d) with color %x\n",
               //        posx * SZ + x, posy * SZ + y, color);
				put_pixel(game->world,
					posx * SZ + x,
					posy * SZ + y, color);
			}
		}
	}
}


void	put_pixel(t_sprite *sprite, int x, int y, int color)
{
	char	*dst;
	
    if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
    {
        fprintf(stderr, "Erro: Tentativa de desenhar fora dos limites da imagem (%d, %d)\n", x, y);
        return;
    }
	dst = sprite->addr + (y * sprite->line_length
			+ x * (sprite->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(sprite->addr
			+ (y * sprite->line_length
				+ x * (sprite->bits_per_pixel / 8)));
	return (color);
}

void	create_map(t_game *game)
{
	int			y;
	int			x;
	t_sprite	*sprite;

 //   printf("Creating map...\n");
	y = -1;
	while (++y < game->map.lines)
	{
		x = -1;
		while (++x < game->map.colun)
		{
            char *sprite_path = get_sprite_path(game, game->map.map[y][x].type);
            if (!sprite_path)
            {
                fprintf(stderr, "Failed to get sprite path for character: %c at (%d, %d)\n", game->map.map[y][x].type, y, x);
                gameover(game);
            }
			game->map.map[y][x].sprt_path = ft_strdup(sprite_path);
			sprite = create_sprite(game, sprite_path);
			create_world(sprite, game, x, y);
			mlx_destroy_image(game->mlx, sprite->img);
			free(sprite);
		}
	}
 //   printf("Map created successfully.\n"); // Mensagem de depuração
}
char	*get_sprite_path(t_game *game, char c)
{
	char	*path;
	int randv;

	randv = rand();
	path = NULL;
	if (c == '1')
	{
		if(randv % 2 == 0)
			path = ft_strdup(WALL);
		else
			path = ft_strdup(WALL2);
	}	
	else if (c == '0' || c == 'C' || c == 'E' || c == 'P' || c == 'M' || c == 'B')
	{
		if(randv % 2 == 0)
			path = ft_strdup(FLOOR);
		else if(randv % 3 == 0)
			path = ft_strdup(FLOOR2);
		else
			path = ft_strdup(FLOOR3);		
	}
	if (!path)
    {
        fprintf(stderr, "Failed to allocate path for character: %c\n", c);
		gameover(game);
    }
	return (path);
}


void	put_map(t_game *game)
{
	int			y;
	int			x;
//	t_tile	**map;
	t_sprite *sprite;
	
	sprite = NULL;
//	map = game->map.map;
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
 //   printf("Map created successfully.\n"); // Mensagem de depuração
}
void    create_character(t_sprite *sprite, t_game *game, int posx, int posy)
{
    int x;
    int y;
    unsigned int color;
	unsigned int trans_color = 0xFFC0CB;

    y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color != trans_color)
            {
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
	}  
}

void	put_tile(t_game *game, int x, int y)
{
    char *sprite_path;
	t_sprite *sprite;
	
	sprite_path = game->map.map[y][x].sprt_path;
	sprite = NULL;
    sprite = create_sprite(game, sprite_path);
    create_world(sprite, game, x, y);
    mlx_destroy_image(game->mlx, sprite->img);
    free(sprite_path);
    free(sprite);

}
