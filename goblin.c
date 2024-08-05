/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/05 20:17:28 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_list_goblin(t_game *game)
{
    game->gbl = NULL;
}

void add_goblin_to_list(t_game *game, int x, int y)
{
    t_goblin *nw_goblin;
    t_goblin *current;

    nw_goblin = new_goblin();
    if (!nw_goblin)
    {
        printf("Error creating goblin.\n");
        free_goblins(game->gbl);
        exit(1);
    }
    init_goblin(nw_goblin);
    nw_goblin->gbl_p.x = x;
    nw_goblin->gbl_p.y = y;
       
    if (game->gbl == NULL)
    {
            game->gbl = nw_goblin;
    }
    else
    {
        current = game->gbl;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = nw_goblin;
    }
}
    
void init_goblin(t_goblin *goblin)
{
    int random_dir;

    goblin->is_alive = 1;
    goblin->current_sprite = 0;
    goblin->is_moving = 0;
    goblin->dx = 0;
    goblin->dy = 0;
    goblin->steps_remaining = 0;
    goblin->step_size = 0;
    goblin->update_interval = 1000 / 60;
    goblin->last_update_time = clock();
    goblin->accumulated_time = 0;
    goblin->dead = ft_strdup(BLOOD);
    goblin->front_sprites[0] = ft_strdup(GOBLIN_FRONT_STAND);
    goblin->front_sprites[1] = ft_strdup(GOBLIN_FRONT_MV1);
    goblin->front_sprites[2] = ft_strdup(GOBLIN_FRONT_MV2);
    goblin->back_sprites[0] = ft_strdup(GOBLIN_BACK_MV1);
    goblin->back_sprites[1] = ft_strdup(GOBLIN_BACK_MV2);
    goblin->back_sprites[2] = ft_strdup(GOBLIN_BACK_MV3);
    goblin->left_sprites[0] = ft_strdup(GOBLIN_LEFT_MV1);
    goblin->left_sprites[1] = ft_strdup(GOBLIN_LEFT_MV2);
    goblin->left_sprites[2] = ft_strdup(GOBLIN_LEFT_MV3);
    goblin->right_sprites[0] = ft_strdup(GOBLIN_RIGHT_MV1);
    goblin->right_sprites[1] = ft_strdup(GOBLIN_RIGHT_MV2);
    goblin->right_sprites[2] = ft_strdup(GOBLIN_RIGHT_MV3);
    random_dir = rand() % 4;
    init_rand_dir_goblin(goblin, random_dir);	 
}
void init_rand_dir_goblin(t_goblin *goblin, int random_dir)
{
    if (random_dir == 0)
        goblin->mv_dir = DIR_UP;
    else if (random_dir == 1)
        goblin->mv_dir = DIR_DOWN;
    else if (random_dir == 2)
        goblin->mv_dir = DIR_LEFT;
    else
        goblin->mv_dir = DIR_RIGHT;
}

t_goblin *new_goblin(void)
{
    t_goblin *new_goblin = (t_goblin *)ft_calloc(1, sizeof(t_goblin));
    if(!new_goblin)
    {
        printf("Error allocating memory for a new goblin.\n");
        return(0);      
    }
    new_goblin->next = NULL;
    
    return new_goblin; 
}
void add_goblin(t_goblin **head, t_goblin *new_goblin) 
{
    if (*head == NULL) 
    {
        *head = new_goblin;
    } 
    else 
    {
        t_goblin *current = *head;
        while(current->next != NULL) 
        {            
            current = current->next;
        }
        current->next = new_goblin;
    }
}

void free_goblins(t_goblin *head) {
    t_goblin *current;
    t_goblin *next;
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
        free(current->gbl);
        free(current);        
        current = next;
    }
}

void put_goblin(t_game *game, t_goblin *goblin, int sprite_index)
{
    char *current_sprite;
    int x = goblin->gbl_p.x;
    int y = goblin->gbl_p.y;

    if (goblin->is_alive)
    {
        if (sprite_index < 0 || sprite_index >= 3)
            sprite_index = 0;
        if (goblin->mv_dir == DIR_UP)
            current_sprite = goblin->back_sprites[sprite_index];
        else if (goblin->mv_dir == DIR_DOWN)
            current_sprite = goblin->front_sprites[sprite_index];
        else if (goblin->mv_dir == DIR_LEFT)
            current_sprite = goblin->left_sprites[sprite_index];
        else if (goblin->mv_dir == DIR_RIGHT)
            current_sprite = goblin->right_sprites[sprite_index];
        else
            current_sprite = goblin->front_sprites[0];
    }
    else
        current_sprite = goblin->dead;
    goblin->gbl = create_sprite(game, current_sprite);
    create_character(goblin->gbl, game, x, y);
}


int move_goblins_check(t_game *game, t_goblin *gbl, int dx, int dy)
{
   if(!gbl->is_alive)
          return (0);            
    int new_x;
    int new_y;
    new_x = gbl->gbl_p.x + dx * SZ;
    new_y = gbl->gbl_p.y + dy * SZ;
    if (game->map.map[new_y / SZ][new_x / SZ].type == '1' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'C' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'E' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'M')
        return 0;
    if (dx == 0 && dy == -1)
        gbl->mv_dir = DIR_UP;
    else if (dx == 0 && dy == 1)
        gbl->mv_dir = DIR_DOWN;
    else if (dx == -1 && dy == 0)
        gbl->mv_dir = DIR_LEFT;
    else if (dx == 1 && dy == 0)
        gbl->mv_dir = DIR_RIGHT;
    return(1); 
}

void move_goblin(t_game *game, t_goblin *gbl, int dx, int dy)
{
    if (gbl->is_moving)
        return;
    int old_x = gbl->gbl_p.x;
    int old_y = gbl->gbl_p.y;

    gbl->dx = dx;                   
    gbl->dy = dy;                           
    gbl->steps_remaining = 10;              
    gbl->step_size = 4;                      
    gbl->update_interval = 1000 / 60;        
    gbl->dest_p.x = gbl->gbl_p.x + dx * 20 * 2; 
    gbl->dest_p.y = gbl->gbl_p.y + dy * 20 * 2;
    gbl->last_update_time = clock();         
    gbl->accumulated_time = 0;            
    gbl->current_sprite = 0;
    gbl->is_moving = 1;
    update_map_tiles(game, old_x, old_y, gbl->dest_p.x, gbl->dest_p.y, 'C');                 
}

void update_goblin_position(t_goblin *gbl)
{
    clock_t current_time = clock();
    int elapsed_time = (current_time - gbl->last_update_time) * 1000 / CLOCKS_PER_SEC;
    gbl->accumulated_time += elapsed_time;
    int time_per_step = gbl->update_interval;
    while (gbl->accumulated_time >= time_per_step && gbl->steps_remaining > 0)
    {
        gbl->gbl_p.x += gbl->dx * gbl->step_size;
        gbl->gbl_p.y += gbl->dy * gbl->step_size;
        gbl->steps_remaining--;
        gbl->current_sprite = (gbl->current_sprite + 1) % 3;
        gbl->accumulated_time -= time_per_step;
    }
    if(gbl->steps_remaining == 0)
    {
        gbl->is_moving = 0;
        gbl->current_sprite = 0;
    }
    gbl->last_update_time = current_time;
}

void move_rand_goblins(t_game *game)
{
    t_goblin *cur_gbl;
    int directions[4][2];
    int dir_index;
    int dx;
    int dy;
    
    cur_gbl = game->gbl;
    init_directions(directions);
    while (cur_gbl != NULL)
    {
        if(cur_gbl->is_alive && rand() % 6 == 0)
        {
            dir_index = rand() % 4;
            dx = directions[dir_index][0];
            dy = directions[dir_index][1];
            if (move_goblins_check(game, cur_gbl, dx, dy))
            {
                move_goblin(game, cur_gbl, dx, dy);
            }           
        } 
        cur_gbl = cur_gbl->next;  
    }     
}

void init_directions(int directions[4][2])
{
    directions[0][0] = 0;
    directions[0][1] = -1;
    directions[1][0] = 0;
    directions[1][1] = 1;
    directions[2][0] = -1;
    directions[2][1] = 0;
    directions[3][0] = 1; 
    directions[3][1] = 0;
}

void update_goblin_sprite_randomly(t_game *game)
{
    t_goblin *current_goblin;
    static int frame_counter = 0;
    frame_counter++;

if (frame_counter >= 180)
{
    current_goblin = game->gbl;
    while (current_goblin != NULL)
    {
        if(rand() % 20)
        {
        current_goblin->mv_dir = rand() % 4;
        put_goblin(game, current_goblin, current_goblin->current_sprite);
        }
        current_goblin = current_goblin->next;
    }
    frame_counter = 0;
}
 
}
