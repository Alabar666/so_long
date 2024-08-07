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

void init_battle(t_game *game)
{
   game->battle.p1_sprt = ft_strdup(CPLAYER);
   game->battle.gbl_sprt = ft_strdup(CGOBLIN);
   game->battle.eny_sprt = ft_strdup(CENEMY);
   game->battle.atk_sprt = ft_strdup(CATACK);
   game->battle.run_sprt = ft_strdup(CRUN);
   game->battle.is_running = 0;

//    goblin->update_interval = 1000 / 60;
  //  goblin->last_update_time = clock();
  //  goblin->accumulated_time = 0;
}
void start_battle(t_game *game)
{

  //  init_battle(game);



    game->is_paused = 1;
  //  game->battle.is_running = 1;
 //   load_combat_screen(game);
    render_battle(game);
 //   load_and_animate_sprites(game);

}

/*
int update_battle_frame(void *param)
{
    t_game *game = (t_game *)param;
    static clock_t last_time = 0;
    clock_t current_time = clock();
    float delta_time = (float)(current_time - last_time) / CLOCKS_PER_SEC;
    
    if (delta_time < 1.0f / 60.0f || game->is_paused)
        return 0;

    game->global_timer += delta_time;
	update_player_position(game);

	last_time = current_time;
    return 0;
} */

void render_battle(t_game *game)
{

    create_battle_screen(game);
    mlx_put_image_to_window(game->mlx, game->win, game->battle.btl_img->img, 0, 0);

}

/*
void	put_player_combat(t_game *game, int sprite_index)
{
    char *current_sprite;
    int x;
    int y;

	x = game->p1.p1_p.x;
	y = game->p1.p1_p.y;

    current_sprite = ft_strdup(CPLAYER);

    game->p1.p1 = create_sprite(game, current_sprite);
    create_character(game->p1.p1, game, x, y);
}*/


void    create_battle(t_sprite *sprite, t_game *game)
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
				put_pixel(game->battle.btl_img, x,	y, color);
			}
		}
	}
}

void	create_battle_screen(t_game *game)
{
	t_sprite	*sprite;

	sprite = create_sprite(game, COMBAT);
	create_battle(sprite, game);
	mlx_destroy_image(game->mlx, sprite->img);
	free(sprite);
}
    /*
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



void load_combat_screen(t_game *game)
{
    // Carregar o sprite de combate
    t_sprite *combat = create_sprite(game, COMBAT);

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

*/


