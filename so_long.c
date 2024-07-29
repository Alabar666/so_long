/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:44 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/29 21:48:43 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

static void	start_world(t_game *game);

#define MALLOC_ERROR    1

int main(int ac, char **av)
{
    srand(time(NULL));
    t_game  game;
    
    if(ac == 2)
    {
        init_list_goblin(&game);
        map_start(av[1], &game);
        start_world(&game);
        init_player(&game);
        init_exit(&game);

  //      init_goblin(&game);
        create_map(&game);
        update_frame(&game, 0);        
 //       put_player_mov(&game);

//        mlx_key_hook(game.win, key_pressed, &game);
 //       mlx_loop_hook(game.mlx, update_frame, &game);
        mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);

        mlx_loop_hook(game.mlx, update_frame, &game);
        mlx_loop(game.mlx);
        /*mlx_hook(game.win, KeyPress, KeyPressMask, key_pressed, &game);
        mlx_loop_hook(game.mlx, update_frame, &game);
        mlx_loop(game.mlx);*/  
        
        mlx_destroy_image(game.mlx, game.world);
        mlx_destroy_window(game.mlx, game.win);
        mlx_destroy_display(game.mlx);
        free(game.mlx);     
    }
    
    
	return (write(2, "Error\nInvalid input\n", 21));
}
static void	start_world(t_game *game)
{
	t_sprite	*world;

    game->lst_gbl_upt = time(NULL);
    game->global_timer = 0;
	world = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
    if (!world)
    {
        fprintf(stderr, "Error\nFailed to allocate memory for world\n");
        exit(MALLOC_ERROR);
    }
	world->img = mlx_new_image(game->mlx,
			game->map.colun * SZ, game->map.lines * SZ);
	if (!world->img)
	{
		free_map(game->map.map);
		exit(0);
	}
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->width = game->map.colun * SZ;
	world->height = game->map.lines * SZ;
	game->world = world;
    
    printf("World created with dimensions: %d x %d\n", world->width, world->height);
}








/*

struct do mlx tem o delta

mlx_init() = inicializa a biblioteca
mlx_new_window = abre uma janela
mlx_hook(KeyPress) = key continuosly pressed
mlx_key_hook(game->wd, put_keys, game); -> key pressed once
mlx_loop_hook = loop to spin the coin and inside move the enemy

//fazer loop antes de encontrar cada C
//função rand da biblioteca mat

VALIDAÇÕES DO MAPA:
- se tem caracter invalido (!= 0, 1, P, E, C)
- se tem somente 1 E e 1 P
- se tem pelo menos um C
- se é fechado por 1s
- tamanho minimo (x + y > 8)
- se é retangular (tamanho das linhas tem que ser igual)
- se tem caminho valido pro P chegar ao E (colectables?) (flood fill)

- tamanho maximo (tamanho da tela do pc) - NAO FIZ
RETORNA mensagem de erro configurável \n

para ser valido, a abertura do mapa tem que ser valida e 
os 4 ultimos digitos tem que ser ".ber"
*/
