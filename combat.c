/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/04 13:08:02 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
double lerp(double a, double b, double t)
{
    return a + t * (b - a);
}

void load_combat_screen(t_game *game)
{

    int screen_width = game->map.width; // Usar as dimensões da tela
    int screen_height = game->map.height;
    t_sprite *combat = create_sprite(game, COMBAT);

    t_sprite *combat_resized = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
    if (!combat_resized)
    {
        ft_printf("Memory allocation failed for resized sprite.\n");
        gameover(game);
        return;
    }
    resize_sprite(combat, combat_resized, screen_width, screen_height);

          mlx_put_image_to_window(game->mlx, game->win, combat_resized->img, 0, 0);
        usleep(5000); // Adjust the delay for smoother transition
    
    mlx_destroy_image(game->mlx, combat->img);
    free(combat);
    mlx_destroy_image(game->mlx, combat_resized->img);
    free(combat_resized);
    }

void resize_sprite(t_sprite *source, t_sprite *destination, int dest_width, int dest_height)
{
    int x, y;
    double src_x, src_y;
    unsigned int color;

    // Crie uma nova imagem para o destino com as novas dimensões
    destination->img = mlx_new_image(source->img, dest_width, dest_height);
    destination->addr = mlx_get_data_addr(destination->img, &destination->bits_per_pixel,
                                          &destination->line_length, &destination->endian);
    destination->width = dest_width;
    destination->height = dest_height;
    for (y = 0; y < destination->height; y++)
    {
        for (x = 0; x < destination->width; x++)
        {
            // Calcular as coordenadas da imagem de origem
            src_x = (double)x * source->width / dest_width;
            src_y = (double)y * source->height / dest_height;

            // Obter a cor do pixel da imagem de origem
            color = get_color_in_pixel(source, (int)src_x, (int)src_y);
            
            // Colocar o pixel na imagem de destino
            put_pixel(destination, x, y, color);
        }
    }
}*/
void load_combat_screen(t_game *game)
{
    // Carregar o sprite de combate
    t_sprite *combat = create_sprite(game, COMBAT2);

    // Criar uma nova imagem para o tamanho da tela
    t_sprite *resized_combat = (t_sprite *)malloc(sizeof(t_sprite));
    resized_combat->width = game->map.width;
    resized_combat->height = game->map.height;
    resized_combat->img = mlx_new_image(game->mlx, resized_combat->width, resized_combat->height);
    resized_combat->addr = mlx_get_data_addr(resized_combat->img, &resized_combat->bits_per_pixel,
                                              &resized_combat->line_length, &resized_combat->endian);

    // Redimensionar a imagem de combate para o tamanho da tela
    resize_image(combat, resized_combat);

    // Limpar a tela para preparar para desenhar o sprite
    mlx_clear_window(game->mlx, game->win);

    for (int y = 0; y < resized_combat->height; y++)
    {
        for (int x = 0; x < resized_combat->width; x++)
        {
            // Desenhar um pixel da imagem na tela
            unsigned int color = get_color_in_pixel(resized_combat, x, y);
            put_pixel(resized_combat, x, y, color);
        }

        // Atualizar a janela com a nova linha de pixels desenhados
        mlx_put_image_to_window(game->mlx, game->win, resized_combat->img, 0, 0);
        usleep(1000); // Ajusta o delay para controlar a velocidade do efeito
    }


    // Desenhar a imagem completa após o efeito
    mlx_put_image_to_window(game->mlx, game->win, resized_combat->img, 0, 0);

    // Liberar a memória usada
 //   mlx_destroy_image(game->mlx, combat->img);
 //   free(combat);
 //   mlx_destroy_image(game->mlx, resized_combat->img);
  //  free(resized_combat);
}
void start_battle(t_game *game)
{
    game->is_paused = 1;
    load_combat_screen(game);

    load_and_animate_sprites(game);

}

void draw_sprite(t_game *game, t_sprite *sprite, int x, int y)
{
    mlx_put_image_to_window(game->mlx, game->win, sprite->img, x, y);
}

void move_sprite(int *x, int *y, int target_x, int target_y, int speed)
{
    if (*x < target_x) *x += speed;
    if (*x > target_x) *x -= speed;
    if (*y < target_y) *y += speed;
    if (*y > target_y) *y -= speed;
}
void load_and_animate_sprites(t_game *game)
{
    // Carregar sprites
    t_sprite *player = create_sprite(game, CPLAYER);
    t_sprite *goblin = create_sprite(game, CGOBLIN);
    t_sprite *atack = create_sprite(game, CATACK);
    t_sprite *run = create_sprite(game, CRUN);

    // Definir posições iniciais e finais
    int player_x = 0, player_y = 0;
    int goblin_x = 0, goblin_y = 0;
    int atack_x = 0, atack_y = game->map.height - 100;
    int run_x = game->map.width - 100, run_y = game->map.height - 100;

    int player_target_x = game->map.width / 4;
    int player_target_y = game->map.height / 2;
    int goblin_target_x = game->map.width / 2;
    int goblin_target_y = game->map.height / 2;

    // Limpar a tela para preparar para desenhar
    mlx_clear_window(game->mlx, game->win);

    while (player_x != player_target_x || player_y != player_target_y ||
           goblin_x != goblin_target_x || goblin_y != goblin_target_y)
    {
        // Mover e desenhar o jogador
        move_sprite(&player_x, &player_y, player_target_x, player_target_y, 2);
        draw_sprite(game, player, player_x, player_y);

        // Mover e desenhar o goblin
        move_sprite(&goblin_x, &goblin_y, goblin_target_x, goblin_target_y, 2);
        draw_sprite(game, goblin, goblin_x, goblin_y);

        // Mover e desenhar os botões
        draw_sprite(game, atack, atack_x, atack_y);
        draw_sprite(game, run, run_x, run_y);

        // Atualizar a tela
        mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);

        // Pequeno atraso para suavizar o movimento
        usleep(5000);
    }

    // Liberar a memória usada
    mlx_destroy_image(game->mlx, player->img);
    free(player);
    mlx_destroy_image(game->mlx, goblin->img);
    free(goblin);
    mlx_destroy_image(game->mlx, atack->img);
    free(atack);
    mlx_destroy_image(game->mlx, run->img);
    free(run);
}

void resize_image(t_sprite *source, t_sprite *destination)
{
    int x, y;
    double src_x, src_y;
    unsigned int color;

    for (y = 0; y < destination->height; y++)
    {
        for (x = 0; x < destination->width; x++)
        {
            // Calcular as coordenadas da imagem de origem
            src_x = (double)x * source->width / destination->width;
            src_y = (double)y * source->height / destination->height;

            // Obter a cor do pixel da imagem de origem
            color = get_color_in_pixel(source, (int)src_x, (int)src_y);
            
            // Colocar o pixel na imagem de destino
            put_pixel(destination, x, y, color);
        }
    }
}




