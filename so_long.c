/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:44 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/16 19:22:20 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

#define MALLOC_ERROR    1
#define WIDTH   400
#define HEIGHT  400

int main(int ac, char **av)
{
    t_game  game;
    
    if(ac == 2)
    {
        map_start(av[1], &game);
        draw_map(&game);
        
        mlx_loop(game.mlx);

        mlx_destroy_image(game.mlx, game.map.img);
        mlx_destroy_window(game.mlx, game.win);
        mlx_destroy_display(game.mlx);
     free(game.mlx);     
    }
    
    
	return (write(2, "Error\nInvalid input\n", 21));
}









/*
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