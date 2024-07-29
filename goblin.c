/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/29 22:08:02 by hluiz-ma         ###   ########.fr       */
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
        printf("Erro ao criar goblin.\n");
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
    {
        goblin->mv_dir = DIR_UP;
        goblin->current_sprite = goblin->back_sprites[0];
    }
    else if (random_dir == 1)
    {
        goblin->mv_dir = DIR_DOWN;
        goblin->current_sprite = goblin->front_sprites[0];
    }
    else if (random_dir == 2)
    {
        goblin->mv_dir = DIR_LEFT;
        goblin->current_sprite = goblin->left_sprites[0];
    }
    else
    {
        goblin->mv_dir = DIR_RIGHT;
        goblin->current_sprite = goblin->right_sprites[0];
    }
}

t_goblin *new_goblin(void)
{
    t_goblin *new_goblin = (t_goblin *)ft_calloc(1, sizeof(t_goblin));
    if(!new_goblin)
    {
        printf("Erro ao alocar memória para um novo goblin.\n");
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
        free(current->gbl);  // Libera o sprite do goblin
        free(current);        
        current = next;
    }
}

void	put_goblin(t_game *game, t_goblin *goblin, int sprite_index)
{
    char *current_sprite;
    int x;
    int y;

	x = goblin->gbl_p.x;
	y = goblin->gbl_p.y;
    
    if (goblin->mv_dir == DIR_UP)
    {
        if (sprite_index < 3)
            current_sprite = goblin->back_sprites[sprite_index];
        else
            current_sprite = goblin->back_sprites[0];
    }    
    else if (goblin->mv_dir == DIR_DOWN)
    {
        if (sprite_index < 3)
            current_sprite = goblin->front_sprites[sprite_index];
        else
            current_sprite = goblin->front_sprites[0];
    } 
    else if (goblin->mv_dir == DIR_LEFT)
    {
        if (sprite_index < 3)
            current_sprite = goblin->left_sprites[sprite_index];
        else
            current_sprite = goblin->left_sprites[0];
    } 
    else if (goblin->mv_dir == DIR_RIGHT)
    {
        if (sprite_index < 3)
            current_sprite = goblin->right_sprites[sprite_index];
        else
            current_sprite = goblin->right_sprites[0];
    } 
    else
        current_sprite = goblin->front_sprites[0];

    goblin->gbl = create_sprite(game, current_sprite);
    create_character(goblin->gbl, game, x, y);
}

int move_goblins_check(t_game *game, t_goblin *gbl, int dx, int dy)
{


   //  if(!gbl->is_alive)
   //         return (0);

            
    int new_x = gbl->gbl_p.x + dx * SZ;
    int new_y = gbl->gbl_p.y + dy * SZ;

    // Verificação de colisão com paredes, colecionáveis e saídas
    if (game->map.map[new_y / SZ][new_x / SZ].type == '1' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'C' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'E' ||
        game->map.map[new_y / SZ][new_x / SZ].type == 'M')
    {
        return 0;
    }
    // Atualizar a direção do goblin
    if (dx == 0 && dy == -1)
        gbl->mv_dir = DIR_UP;
    else if (dx == 0 && dy == 1)
        gbl->mv_dir = DIR_DOWN;
    else if (dx == -1 && dy == 0)
        gbl->mv_dir = DIR_LEFT;
    else if (dx == 1 && dy == 0)
        gbl->mv_dir = DIR_RIGHT;

    move_goblin(game, gbl, dx, dy);
    return 1;


/*
      //  UP;
        if(game->map.map[(gbl->gbl_p.y / SZ) - 1][gbl->gbl_p.x / SZ].type != '1' ||
            game->map.map[(gbl->gbl_p.y / SZ) - 1][gbl->gbl_p.x / SZ].type != 'C' ||
             game->map.map[(gbl->gbl_p.y / SZ) - 1][gbl->gbl_p.x / SZ].type != 'E') 
            return(gbl->mv_dir = DIR_UP, move_goblin(game, gbl, 0, -1), 1);

      //  DOWN;
        if(game->map.map[(gbl->gbl_p.y / SZ) + 1][gbl->gbl_p.x / SZ].type != '1' ||
            game->map.map[(gbl->gbl_p.y / SZ) + 1][gbl->gbl_p.x / SZ].type != 'C' ||
             game->map.map[(gbl->gbl_p.y / SZ) + 1][gbl->gbl_p.x / SZ].type != 'E') 
            return(gbl->mv_dir = DIR_DOWN, move_goblin(game, gbl, 0, +1), 1);

     //   LEFT;
        if(game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) -1].type != '1' ||
            game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) -1].type != 'C' ||
             game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) -1].type != 'E') 
            return(gbl->mv_dir = DIR_LEFT, move_goblin(game, gbl, -1, 0), 1);

     //   RIGHT;
        if(game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) +1].type != '1' ||
            game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) +1].type != 'C' ||
             game->map.map[gbl->gbl_p.y / SZ][(gbl->gbl_p.x / SZ) +1].type != 'E')
            return(gbl->mv_dir = DIR_RIGHT, move_goblin(game, gbl, 1, 0), 1);
            */
    return(1); 
}

void move_goblin(t_game *game, t_goblin *gbl, int dx, int dy)
{
    int steps = 4;
    int step_size = 10;
    int i;
    
    i = 0;
    while (i < steps)
    {
        gbl->gbl_p.x += dx * step_size;
        gbl->gbl_p.y += dy * step_size;
 //       update_all_goblins(game);
        put_goblin(game, gbl, i);
    //    mlx_put_image_to_window(game->mlx, game->win, game->world->img, 0, 0);
  //      update_frame(game, i);
        usleep(50000); // Atraso para criar a animação
        i++;
    }
}

void move_rand_goblins(t_game *game, t_goblin *gbl)
{
    t_goblin *cur_gbl;
    int move_count;
    int max_moves;
    int directions[4][2];
    int dir_index;
    int dx;
    int dy;

    cur_gbl = gbl;
    move_count = 0;
    max_moves = game->map.goblin / 3;
    if(max_moves == 0)
        max_moves = 1;
    init_directions(directions);
    while (cur_gbl != NULL)
    {
        if(cur_gbl->is_alive && move_count < max_moves && rand() % 2 == 0)
        {
            dir_index = rand() % 4;
            dx = directions[dir_index][0];
            dy = directions[dir_index][1];
            update_goblin_sprite_randomly(cur_gbl);
            if (move_goblins_check(game, cur_gbl, dx, dy))
                move_count++;            
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
void update_goblin_sprite_randomly(t_goblin *gbl)
{
	int random_dir;

    if (rand() % 2 == 0) // 50% de chance
    {
        random_dir = rand() % 3;
        if (gbl->mv_dir == DIR_UP || gbl->mv_dir == DIR_DOWN)
        {
            select_vertical_sprite(gbl, random_dir);
        }
        else if (gbl->mv_dir == DIR_LEFT || gbl->mv_dir == DIR_RIGHT)
        {
            select_horizontal_sprite(gbl, random_dir);
        }
    }
}

void select_horizontal_sprite(t_goblin *gbl, int random_dir)
{
    if (gbl->mv_dir == DIR_LEFT)
    {
        if (random_dir == 0)
            gbl->current_sprite = gbl->back_sprites[0];
        else if (random_dir == 1)
            gbl->current_sprite = gbl->front_sprites[0];
        else
            gbl->current_sprite = gbl->right_sprites[0];
    }
    else if (gbl->mv_dir == DIR_RIGHT)
    {
        if (random_dir == 0)
            gbl->current_sprite = gbl->back_sprites[0];
        else if (random_dir == 1)
            gbl->current_sprite = gbl->front_sprites[0];
        else
            gbl->current_sprite = gbl->left_sprites[0];
    }
}
void select_vertical_sprite(t_goblin *gbl, int random_dir)
{
    if (gbl->mv_dir == DIR_UP)
    {
        if (random_dir == 0)
            gbl->current_sprite = gbl->front_sprites[0];
        else if (random_dir == 1)
            gbl->current_sprite = gbl->left_sprites[0];
        else
            gbl->current_sprite = gbl->right_sprites[0];
    }
    else if (gbl->mv_dir == DIR_DOWN)
    {
        if (random_dir == 0)
            gbl->current_sprite = gbl->back_sprites[0];
        else if (random_dir == 1)
            gbl->current_sprite = gbl->left_sprites[0];
        else
            gbl->current_sprite = gbl->right_sprites[0];
    }
}


void update_all_goblins(t_game *game)
{
    t_goblin *current_goblin = game->gbl; // Começa com o primeiro goblin na lista

    while (current_goblin != NULL)
    {

        // Atualiza o goblin atual
        put_goblin(game, current_goblin, 0);

        // Passa para o próximo goblin na lista
        current_goblin = current_goblin->next;
    }
}
