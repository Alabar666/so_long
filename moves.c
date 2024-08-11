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

/*
int key_pressed(int key, t_game *game) 
{
    if (key == ESC && !game->is_paused) 
    {
        gameover(game);
        return 0;
    }

    if (game->battle.is_running) 
        return handle_battle_keys(key, game);
    else
        return handle_player_movement(key, game);
}

int handle_player_movement(int key, t_game *game) 
{
    if (game->p1.is_moving || !game->p1.alive)
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

int handle_battle_keys(int key, t_game *game) 
{
    if (key == ENTER) 
    {
        if (game->run_selected) 
        {
            game->message_display_duration = 0;
            while (game->message_display_duration++ < 1250000) 
            {
                mlx_string_put(game->mlx, game->win, 
                    (game->world->width - 200) / 2, 
                    (game->world->height - 50) / 2, 
                    0xFFFF00, 
                    "The Goblin will not allow you to escape.");
            }
            return 0;
        } 
        else 
        {   
            game->wait_input = 0;
            close_battle(game);  
            return 0; 
        }    
    }
    battle_keys(key, game);
    return 0;
}*/

int key_pressed(int key, t_game *game){
    
    if (key == ESC && !game->is_paused)
    {
        gameover(game);
    }
    if (game->battle.is_running)
    {
        if (key == ENTER)
         {
            if (game->run_selected)
            {
                game->message_display_duration = 0;
                while(game->message_display_duration++ < 1000000)
                    mlx_string_put(game->mlx, game->win, ((game->world->width - 200) / 2), ((game->world->height - 50) / 2), 0xFFFF00, "The Goblin will not allow you to escape.");
                return 0;
            }
            else
            {   
                printf("test"); 
             game->wait_input = 0;
             close_battle(game);  
             return 0; 
            }    
          }
        battle_keys(key, game);
    }
    else
    {
    if (game->p1.is_moving || !game->p1.alive)
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
    }
    return (0);
}

 
void move_player(t_game *game, int dx, int dy)
{
    if (game->p1.is_moving)
        return;
    int old_x = game->p1.p1_p.x;
    int old_y = game->p1.p1_p.y;

    game->p1.dx = dx;                           
    game->p1.dy = dy;                        
    game->p1.steps_remaining = 10;               
    game->p1.step_size = 4;                    
    game->p1.update_interval = 1000 / 60;     
    game->p1.dest_p.x = game->p1.p1_p.x + dx * 20 * 2;  
    game->p1.dest_p.y = game->p1.p1_p.y + dy * 20 * 2; 
    game->p1.last_update_time = clock();         
    game->p1.accumulated_time = 0;              
    game->p1.current_sprite = 0;
    game->p1.is_moving = 1;
    game->p1.moves++;
    ft_printf("Moves amount: %i\n", game->p1.moves); 
    put_moves(game);
    check_position(game, game->p1.dest_p.x, game->p1.dest_p.y); 
    update_map_tiles(game, old_x, old_y, game->p1.dest_p.x, game->p1.dest_p.y, 'P');  
}

void update_player_position(t_game *game)
{
    if (!game) {
        printf("Erro: game é NULL\n");
        return;
    }
    int elapsed_time;
    int time_per_step;

    clock_t current_time = clock();
    elapsed_time = (current_time - game->p1.last_update_time) * 1000 / CLOCKS_PER_SEC;
    game->p1.accumulated_time += elapsed_time;
    time_per_step = game->p1.update_interval;
    while (game->p1.accumulated_time >= time_per_step && game->p1.steps_remaining > 0)
    {
        game->p1.p1_p.x += game->p1.dx * game->p1.step_size;
        game->p1.p1_p.y += game->p1.dy * game->p1.step_size;
        game->p1.steps_remaining--;
        game->p1.current_sprite = (game->p1.current_sprite + 1) % 3;
        game->p1.accumulated_time -= time_per_step;
    }
        if (game->p1.steps_remaining == 0)
    {
        game->p1.is_moving = 0;
        game->p1.current_sprite = 0;
    }
    game->p1.last_update_time = current_time;    
}

void put_moves(t_game *game)
{
    char *move_str;
    int balloon_x;
    int balloon_y;
    int text_x;
    int text_y; 

    move_str = ft_itoa(game->p1.moves);

    balloon_x = game->p1.p1_p.x + 40;
    balloon_y = game->p1.p1_p.y - 40;
    text_x = balloon_x + 16;
    text_y = balloon_y + 19;
    if(game->p1.moves != 0)
    {
        game->p1.bl = create_sprite(game, game->p1.pl_ballom);
        create_character(game->p1.bl, game, balloon_x, balloon_y);
    }
    mlx_string_put(game->mlx, game->win, text_x, text_y, 0xFFFF00, move_str);
    free(move_str);
}

void update_map_tiles(t_game *game, int old_x, int old_y, int new_x, int new_y, char type)
{
    int map_old_x;
    int map_old_y;
    int map_new_x;
    int map_new_y;

    map_old_x = old_x / SZ;
    map_old_y = old_y / SZ;
    map_new_x = new_x / SZ;
    map_new_y = new_y / SZ;
    if(game->map.map[map_new_y][map_new_x].type == '0')
    {
        game->map.map[map_old_y][map_old_x].type = '0';
       game->map.map[map_new_y][map_new_x].type = type;
    }
}

void check_position(t_game *game, int dx, int dy) 
{
    t_goblin *cur_gbl = game->gbl;
    char enemy_type;

    enemy_type = game->map.map[dy / 40][dx / 40].type;

    if (dx < 0 || dx >= game->map.width || dy < 0 || dy >= game->map.height) 
        return;
 
    if (enemy_type == 'C' || enemy_type == 'M') 
    {
        while (cur_gbl != NULL) {
            if (cur_gbl->gbl_p.x == dx && cur_gbl->gbl_p.y == dy && cur_gbl->is_alive) {
                cur_gbl->is_alive = 0;
                game->map.map[dy/ 40][dx/ 40].type = 'B';
                game->map.goblin--;
                start_battle(game, enemy_type);
                break;
            }
            cur_gbl = cur_gbl->next;
        }
    }
    if(enemy_type == 'M')
    {
        start_battle(game, enemy_type);
        ft_printf("You are dead!\n");
        game->p1.p1 = create_sprite(game, PDEAD);
        game->p1.alive = 0;
        if(!game->wait_input && !game->p1.alive)
            {
                usleep(900000);
             gameover(game);
            }
    }
    if(game->map.goblin == 0 && enemy_type == 'E')
    {
        ft_printf("You saved the priestess!\n");
        usleep(900000);
        gameover(game);
    }
}

/*
void check_position(t_game *game, int dx, int dy) 
{
    if (dx < 0 || dx >= game->map.width || dy < 0 || dy >= game->map.height) 
        return;

    handle_goblins(game, dx, dy);
    handle_enemies_and_victory(game, dx, dy);
}



void handle_goblins(t_game *game, int dx, int dy) 
{
    t_goblin *cur_gbl = game->gbl;
    char enemy_type;

    enemy_type = game->map.map[dy / SZ][dx / SZ].type;

    if (enemy_type != 'C' && enemy_type != 'M')
        return;

    while (cur_gbl != NULL) {
        if (cur_gbl->gbl_p.x == dx && cur_gbl->gbl_p.y == dy && cur_gbl->is_alive) {
            cur_gbl->is_alive = 0;
            game->map.map[dy / SZ][dx / SZ].type = 'B';
            game->map.goblin--;
            start_battle(game, enemy_type);
            break;
        }
        cur_gbl = cur_gbl->next;
    }
}

void handle_enemies_and_victory(t_game *game, int dx, int dy) 
{
    char enemy_type = game->map.map[dy / SZ][dx / SZ].type;

    if (enemy_type == 'M') {
        start_battle(game, enemy_type);
        ft_printf("You are dead!\n");
        game->p1.p1 = create_sprite(game, PDEAD);
        game->p1.alive = 0;
        if (!game->wait_input && !game->p1.alive) {
            usleep(900000);
            gameover(game);
        }
    }

    if (game->map.goblin == 0 && enemy_type == 'E') {
        ft_printf("You saved the priestess!\n");
        usleep(900000);
        gameover(game);
    }
}
*/