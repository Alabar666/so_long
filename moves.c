/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:20:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/25 19:38:47 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int key_pressed(int key, t_game *game){
    
    if (key == ESC)
    {
        gameover(game);
    }
    else if (game->is_moving)
        return 0;
    else if (key == KEY_W || key == UP)
    {
        if(game->map.map[(game->p1.p1_p.y / SZ) - 1][game->p1.p1_p.x / SZ].type != '1') 
            return(game->p1.mv_dir = DIR_UP, move_player(game, 0, -1), 0);
    }
    else if (key == KEY_S || key == DOWN)
    {
        if(game->map.map[(game->p1.p1_p.y / SZ) + 1][game->p1.p1_p.x / SZ].type != '1') 
            return(game->p1.mv_dir = DIR_DOWN, move_player(game, 0, +1), 0);
    }
    else if (key == KEY_A || key == LEFT)
    {
        if(game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) -1].type != '1') 
            return(game->p1.mv_dir = DIR_LEFT, move_player(game, -1, 0), 0);
    }
    else if (key == KEY_D || key == RIGHT)
    {
        if(game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) +1].type != '1') 
            return(game->p1.mv_dir = DIR_RIGHT, move_player(game, 1, 0), 0);
    }
    return (0);
}
/*
void key_pressed(int key, t_game *game)
{
    if (key == ESC)
    {
        gameover(game);
    }
    if (key == KEY_W || key == UP)
    {
        if (game->map.map[(game->p1.p1_p.y / SZ) - 1][game->p1.p1_p.x / SZ].type != '1')
        {
            game->p1.mv_dir = DIR_UP;
            // Não mova o jogador aqui
        }
    }
    else if (key == KEY_S || key == DOWN)
    {
        if (game->map.map[(game->p1.p1_p.y / SZ) + 1][game->p1.p1_p.x / SZ].type != '1')
        {
            game->p1.mv_dir = DIR_DOWN;
            // Não mova o jogador aqui
        }
    }
    else if (key == KEY_A || key == LEFT)
    {
        if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) - 1].type != '1')
        {
            game->p1.mv_dir = DIR_LEFT;
            // Não mova o jogador aqui
        }
    }
    else if (key == KEY_D || key == RIGHT)
    {
        if (game->map.map[game->p1.p1_p.y / SZ][(game->p1.p1_p.x / SZ) + 1].type != '1')
        {
            game->p1.mv_dir = DIR_RIGHT;
            // Não mova o jogador aqui
        }
    }
}*/
/*
void move_player(t_game *game, int dx, int dy)
{
    int steps = 4; // Número de passos para completar o movimento
    int step_size = 10; // Tamanho de cada passo em pixels
    int i;
    int x;
    int y;

    
    i = 0;
    while (i < steps)
    {

        game->p1.p1_p.x += dx * step_size;
        game->p1.p1_p.y += dy * step_size;
        put_player(game, i);

        //render_game(game);
     //   usleep(50000); // Delay para suavizar o movimento
        i++;
    }
    game->p1.moves++;
    
    x = game->p1.p1_p.x / 40;
    y = game->p1.p1_p.y / 40;
    if (game->map.map[y][x].type == 'C')
	{
		game->map.goblin -= 1;
		game->map.map[y][x].type = 'B';
  //      game->map.map[y][x].sprt_path = BLOOD;
        
	}
    else if (game->map.map[y][x].type == 'E' && game->map.goblin == 0)
	{
		printf("Ganhou");
		gameover(game);
	}
    
}
*//*
void move_player(t_game *game, int dx, int dy)
{
    game->p1.dx = dx;
    game->p1.dy = dy;
    game->p1.steps_remaining = 20; // Número de passos para completar o movimento
    game->p1.step_size = 2;        // Tamanho de cada passo em pixels
    game->p1.update_interval = 1000 / 30; // Atualizar 60 vezes por segundo
    game->p1.last_update_time = clock(); 
}*/

void move_player(t_game *game, int dx, int dy)
{
    if (game->is_moving)
        return;


    game->p1.dx = dx;                            // Define a direção do movimento no eixo x
    game->p1.dy = dy;                            // Define a direção do movimento no eixo y
    game->p1.steps_remaining = 10;               // Define o número de passos para completar o movimento
    game->p1.step_size = 4;                      // Define o tamanho de cada passo em pixels
    game->p1.update_interval = 1000 / 60;        // Define o intervalo de atualização
    game->p1.dest_p.x = game->p1.p1_p.x + dx * 20 * 2;  // Calcula a posição de destino no eixo x
    game->p1.dest_p.y = game->p1.p1_p.y + dy * 20 * 2;  // Calcula a posição de destino no eixo y
    game->p1.last_update_time = clock();         // Define o tempo do último movimento
    game->p1.accumulated_time = 0;               // Inicializa o tempo acumulado
    game->p1.current_sprite = 0;
        game->is_moving = 1;                  // Inicializa o índice do sprite (para animação)
}

void update_player_position(t_game *game)
{
    if (!game) {
        printf("Erro: game é NULL\n");
        return;
    }

    clock_t current_time = clock();
    int elapsed_time = (current_time - game->p1.last_update_time) * 1000 / CLOCKS_PER_SEC;
    game->p1.accumulated_time += elapsed_time;

    // Define a quantidade de tempo que deve acumular para mover um passo
    int time_per_step = game->p1.update_interval;

    // Enquanto tivermos acumulado tempo suficiente para pelo menos um passo
    while (game->p1.accumulated_time >= time_per_step && game->p1.steps_remaining > 0)
    {
        printf("Atualizando posição do jogador: x=%d, y=%d\n", game->p1.p1_p.x, game->p1.p1_p.y);

        // Atualiza a posição do jogador
        game->p1.p1_p.x += game->p1.dx * game->p1.step_size;
        game->p1.p1_p.y += game->p1.dy * game->p1.step_size;
        game->p1.steps_remaining--;

        printf("Nova posição do jogador: x=%d, y=%d\n", game->p1.p1_p.x, game->p1.p1_p.y);
        printf("%d\n", game->p1.current_sprite);
        // Atualiza o índice do sprite
        game->p1.current_sprite = (game->p1.current_sprite + 1) % 3; // Cicla entre 0, 1 e 2

        // Reduz a quantidade de tempo acumulado
        game->p1.accumulated_time -= time_per_step;
    }
        if (game->p1.steps_remaining == 0)
    {
        game->is_moving = 0;
        game->p1.current_sprite = 0;
    }

    // Atualiza o tempo do último movimento
    game->p1.last_update_time = current_time;
}
















/*

int key_pressed(int key, t_game *game){
    
    if (key == ESC)
    {
        gameover(game);
    }
    else if (game->p1.mv_dir != STAND)
		return ;
    else if (key == KEY_W || key == UP)
    {
        if(game->map.map[game->p1.p1_p.y - 1][game->p1.p1_p.x] != 1)    
           return(game->p1.p1_p.y = UP, move_dir(game), 0);
 //       game->map.map[game->p1.x][game->p1.y] = '0';
    }
    else if (key == KEY_S || key == DOWN)
    {
        if(game->map.map[game->p1.p1_p.y + 1][game->p1.p1_p.x] != 1)    
        return(game->p1.p1_p.y = DOWN, move_dir(game), 0);
    }
    else if (key == KEY_D || key == RIGHT)
    {
        if(game->map.map[game->p1.p1_p.y][game->p1.p1_p.x + 1] != 1)    
        return(game->p1.p1_p.x = RIGHT, move_dir(game), 0);
    }
    else if (key == KEY_A || key == LEFT)
    {
        if(game->map.map[game->p1.p1_p.y][game->p1.p1_p.x - 1] != 1)    
        return(game->p1.p1_p.x = LEFT, move_dir(game), 0);
    }
    return(0);
}

t_pos	move_dir(int dir, int size)
{
    t_pos pos;

    pos.x = 0;
    pos.y = 0;
        
	if (dir == DIR_LEFT)
		pos.x = SZ * -1;
	else if (dir == DIR_RIGHT)
		pos.x = SZ;
	else if (dir == DIR_UP)
		pos.y = SZ;
	else if (dir == DIR_DOWN)
		pos.y = SZ * -1;
    return(pos);    
}
t_pos new_pos(t_pos ps1, t_pos ps2)
{
    t_pos ps3;
    
    ps3.x = ps1.x + ps2.x;
    ps3.y = ps1.y + ps2.y;
    return(ps3);
}





void player_mov(t_game *game, int dir)
{
    char c;
    t_pos mov;
    t_pos new_mov;

    if(game->p1.face != STAND)
        return;
    
    game->p1.face = dir;    
    mov = move_dir(game->p1.face, SZ);
    new_mov = new_pos(game->p1.p1_p, mov);
    c = game->map.map[y][x];
    if(c == '1')
        return;
    game->p1.p1_p = new_mov;    
    game->p1.moves += 1;
    printf("Steps: %i\n", game->p1.moves);  
}
*/
