/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:20:13 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/21 16:57:32 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int key_pressed(int key, t_game *game){
    
    if (key == ESC)
    {
        gameover(game);
    }
    else if (key == KEY_W || key == UP)
    {
        if(game->map.map[(game->p1.p1_p.y / 40) - 1][game->p1.p1_p.x / 40].type != '1') 
            return(game->p1.mv_dir = DIR_UP, move_player(game, 0, -1), 0);
    }
    else if (key == KEY_S || key == DOWN)
    {
        if(game->map.map[(game->p1.p1_p.y / 40) + 1][game->p1.p1_p.x / 40].type != '1') 
            return(game->p1.mv_dir = DIR_DOWN, move_player(game, 0, +1), 0);
    }
    else if (key == KEY_A || key == LEFT)
    {
        if(game->map.map[game->p1.p1_p.y / 40][(game->p1.p1_p.x / 40) -1].type != '1') 
            return(game->p1.mv_dir = DIR_LEFT, move_player(game, -1, 0), 0);
    }
    else if (key == KEY_D || key == RIGHT)
    {
        if(game->map.map[game->p1.p1_p.y / 40][(game->p1.p1_p.x / 40) +1].type != '1') 
            return(game->p1.mv_dir = DIR_RIGHT, move_player(game, 1, 0), 0);
    }
    return (0);
}

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
        update_frame(game, i);
        usleep(50000); // Atraso para criar a animação
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
/*
    if (game->map.map[dy][dx].type == 'C')
	{
		game->map.goblin -= 1;
		game->map.map[dy][dx].type = 'B';
        game->map.map[dy][dx].sprt_path = BLOOD;
	}
    else if (game->map.map[dy][dx].type == 'E' && game->map.goblin == 0)
	{
		printf("Ganhou");
		gameover(game);
	}
*/



















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
