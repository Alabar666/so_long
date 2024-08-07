/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/05 20:17:36 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_list_enemy(t_game *game)
{
    game->eny = NULL;
}

void add_enemy_to_list(t_game *game, int x, int y)
{
    t_enemy *nw_enemy;
    t_enemy *current;

    nw_enemy = new_enemy();
    if (!nw_enemy)
    {
        printf("Error creating enemy.\n");
        free_enemys(game->eny);
        exit(1);
    }
    init_enemy(nw_enemy);
    nw_enemy->eny_p.x = x;
    nw_enemy->eny_p.y = y;       
    if (game->eny == NULL)
    {
            game->eny = nw_enemy;
    }
    else
    {
        current = game->eny;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = nw_enemy;
    }
}
    
void init_enemy(t_enemy *enemy)
{
    int random_dir;

    enemy->is_alive = 1;
    enemy->current_sprite = 0;
    enemy->is_moving = 0;
    enemy->dx = 0;
    enemy->dy = 0;
    enemy->steps_remaining = 0;
    enemy->step_size = 0;
    enemy->update_interval = 1000 / 60;
    enemy->last_update_time = clock();
    enemy->accumulated_time = 0;
    enemy->dead = ft_strdup(BLOOD);
    enemy->front_sprites[0] = ft_strdup(ENEMY_FRONT_STAND);
    enemy->front_sprites[1] = ft_strdup(ENEMY_FRONT_MV1);
    enemy->front_sprites[2] = ft_strdup(ENEMY_FRONT_MV2);
    enemy->back_sprites[0] = ft_strdup(ENEMY_BACK_MV1);
    enemy->back_sprites[1] = ft_strdup(ENEMY_BACK_MV2);
    enemy->back_sprites[2] = ft_strdup(ENEMY_BACK_MV3);
    enemy->left_sprites[0] = ft_strdup(ENEMY_LEFT_MV1);
    enemy->left_sprites[1] = ft_strdup(ENEMY_LEFT_MV2);
    enemy->left_sprites[2] = ft_strdup(ENEMY_LEFT_MV3);
    enemy->right_sprites[0] = ft_strdup(ENEMY_RIGHT_MV1);
    enemy->right_sprites[1] = ft_strdup(ENEMY_RIGHT_MV2);
    enemy->right_sprites[2] = ft_strdup(ENEMY_RIGHT_MV3);
    random_dir = rand() % 4;
    init_rand_dir_enemy(enemy, random_dir);	 
}
void init_rand_dir_enemy(t_enemy *enemy, int random_dir)
{
    if (random_dir == 0)
        enemy->mv_dir = DIR_UP;
    else if (random_dir == 1)
        enemy->mv_dir = DIR_DOWN;
    else if (random_dir == 2)
        enemy->mv_dir = DIR_LEFT;
    else
        enemy->mv_dir = DIR_RIGHT;
}

t_enemy *new_enemy(void)
{
    t_enemy *new_enemy = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
    if(!new_enemy)
    {
        printf("Error allocating memory for a new enemy.\n");
        return(0);      
    }
    new_enemy->next = NULL;
    
    return new_enemy; 
}
void add_enemy(t_enemy **head, t_enemy *new_enemy) 
{
    if (*head == NULL) 
    {
        *head = new_enemy;
    } 
    else 
    {
        t_enemy *current = *head;
        while(current->next != NULL) 
        {            
            current = current->next;
        }
        current->next = new_enemy;
    }
}

void free_enemys(t_enemy *head) {
    t_enemy *current;
    t_enemy *next;
    int i;
    
    current = head;
    i = 0;
    while (current != NULL) 
    {
        next = current->next;
        while (i < 3) 
        {
            free(current->front_sprites[i]);
            free(current->back_sprites[i]);
            free(current->left_sprites[i]);
            free(current->right_sprites[i]);
            i++;
        }
        free(current->eny);
        free(current);        
        current = next;
    }
}

void put_enemy(t_game *game, t_enemy *enemy, int sprite_index)
{
    char *current_sprite;
    int x = enemy->eny_p.x;
    int y = enemy->eny_p.y;

    if (enemy->is_alive)
    {
        if (sprite_index < 0 || sprite_index >= 3)
            sprite_index = 0;
        if (enemy->mv_dir == DIR_UP)
            current_sprite = enemy->back_sprites[sprite_index];
        else if (enemy->mv_dir == DIR_DOWN)
            current_sprite = enemy->front_sprites[sprite_index];
        else if (enemy->mv_dir == DIR_LEFT)
            current_sprite = enemy->left_sprites[sprite_index];
        else if (enemy->mv_dir == DIR_RIGHT)
            current_sprite = enemy->right_sprites[sprite_index];
        else
            current_sprite = enemy->front_sprites[0];
    }
    else
        current_sprite = enemy->dead;

    enemy->eny = create_sprite(game, current_sprite);
    create_character(enemy->eny, game, x, y);
}


int move_enemys_check(t_game *game, t_enemy *eny, int dx, int dy)
{
   if(!eny->is_alive)
          return (0);            
    int new_x;
    int new_y;
    new_x = eny->eny_p.x + dx * SZ;
    new_y = eny->eny_p.y + dy * SZ;
    if (game->map.map[new_y / SZ][new_x / SZ].type == '1' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'C' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'E' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'M')
        return 0;
    if (dx == 0 && dy == -1)
        eny->mv_dir = DIR_UP;
    else if (dx == 0 && dy == 1)
        eny->mv_dir = DIR_DOWN;
    else if (dx == -1 && dy == 0)
        eny->mv_dir = DIR_LEFT;
    else if (dx == 1 && dy == 0)
        eny->mv_dir = DIR_RIGHT;
    return(1); 
}

void move_enemy(t_game *game, t_enemy *eny, int dx, int dy)
{
    if (eny->is_moving)
        return;
    int old_x = eny->eny_p.x;
    int old_y = eny->eny_p.y;

    eny->dx = dx;                   
    eny->dy = dy;                           
    eny->steps_remaining = 10;              
    eny->step_size = 4;                      
    eny->update_interval = 1000 / 60;        
    eny->dest_p.x = eny->eny_p.x + dx * 20 * 2; 
    eny->dest_p.y = eny->eny_p.y + dy * 20 * 2;
    eny->last_update_time = clock();         
    eny->accumulated_time = 0;            
    eny->current_sprite = 0;
    eny->is_moving = 1;
    update_map_tiles(game, old_x, old_y, eny->dest_p.x, eny->dest_p.y, 'M');                 
}

void update_enemy_position(t_enemy *eny)
{
    clock_t current_time = clock();
    int elapsed_time = (current_time - eny->last_update_time) * 1000 / CLOCKS_PER_SEC;
    eny->accumulated_time += elapsed_time;
    int time_per_step = eny->update_interval;
    while (eny->accumulated_time >= time_per_step && eny->steps_remaining > 0)
    {
        eny->eny_p.x += eny->dx * eny->step_size;
        eny->eny_p.y += eny->dy * eny->step_size;
        eny->steps_remaining--;
        eny->current_sprite = (eny->current_sprite + 1) % 3;
        eny->accumulated_time -= time_per_step;
    }
    if(eny->steps_remaining == 0)
    {
        eny->is_moving = 0;
        eny->current_sprite = 0;
    }
    eny->last_update_time = current_time;
}

void move_rand_enemys(t_game *game)
{
    t_enemy *cur_eny;
    int directions[4][2];
    int dir_index;
    int dx;
    int dy; 

    cur_eny = game->eny;
    init_directions(directions);
    while (cur_eny != NULL)
    {
        if(cur_eny->is_alive && rand() % 2 == 0)
        {
            dir_index = rand() % 4;
            dx = directions[dir_index][0];
            dy = directions[dir_index][1];
            if (move_enemys_check(game, cur_eny, dx, dy))
            {
                move_enemy(game, cur_eny, dx, dy);
            }
        }
        cur_eny = cur_eny->next;
    }       
}

void update_enemy_sprite_randomly(t_game *game)
{
    t_enemy *current_enemy;
    static int frame_counter = 0;
    frame_counter++;

if (frame_counter >= 180)
{
    current_enemy = game->eny;
    while (current_enemy != NULL)
    {
        if(rand() % 20)
        {
        current_enemy->mv_dir = rand() % 4;
        put_enemy(game, current_enemy, current_enemy->current_sprite);
        }
        current_enemy = current_enemy->next;
    }
    frame_counter = 0;
}
 
}
