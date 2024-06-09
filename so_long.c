/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:44 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/09 18:17:13 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx_int.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH   400
#define HEIGHT  400


int main()
{
    void *mlx_connection;
    void *mlx_window;
    
    mlx_connection = mlx_init();
    if (NULL == mlx_connection)
        return(MALLOC_ERROR);

        
    mlx_window = mlx_new_window(mlx_connection,
        HEIGHT,/*size_x*/
        WIDTH,/*size_y*/
        "The Slayer");/*title*/
    if(NULL == mlx_window){
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return(MALLOC_ERROR);
    }


    mlx_loop(mlx_connection);


    mlx_destroy_window(mlx_connection, mlx_window);
    mlx_destroy_display(mlx_connection);
    free(mlx_connection);

    return (0);    
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