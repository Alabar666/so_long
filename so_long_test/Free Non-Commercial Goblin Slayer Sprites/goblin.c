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


    goblin->dx = 0;
    goblin->dy = 0;
    goblin->steps_remaining = 0;
    goblin->step_size = 0;
    goblin->update_interval = 1000 / 60;
    goblin->last_update_time = clock();
    goblin->accumulated_time = 0;

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
    goblin->current_sprite = 0;
    random_dir = rand() % 4;
    init_rand_dir_goblin(goblin, random_dir);	 
}
void init_rand_dir_goblin(t_goblin *goblin, int random_dir)
{
    if (random_dir == 0)
    {
        goblin->mv_dir = DIR_UP;
//        goblin->current_sprite = goblin->back_sprites[0];
    }
    else if (random_dir == 1)
    {
        goblin->mv_dir = DIR_DOWN;
 //       goblin->current_sprite = goblin->front_sprites[0];
    }
    else if (random_dir == 2)
    {
        goblin->mv_dir = DIR_LEFT;
//        goblin->current_sprite = goblin->left_sprites[0];
    }
    else
    {
        goblin->mv_dir = DIR_RIGHT;
 //       goblin->current_sprite = goblin->right_sprites[0];
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

    move_goblin(gbl, dx, dy);
    return 1;

    return(1); 
}
/*
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
        usleep(50000); // Atraso para criar a animação
        render_game(game);
        i++;
        printf("Gbl X: %d, Gbl Y: %d\n", gbl->gbl_p.x, gbl->gbl_p.y);
    }
}*//*
void move_goblin(t_game *game, t_goblin *gbl, int dx, int dy, float delta_time)
{
    static double last_update = 0;
    double current_time = game->global_timer;
    int step_size = 10; // Tamanho de cada passo em pixels
    double update_interval = 0.05; // Intervalo de atualização em segundos

    // Atualize a posição e animação do goblin
    if (current_time - last_update >= update_interval) {
        gbl->gbl_p.x += dx * step_size * delta_time;
        gbl->gbl_p.y += dy * step_size * delta_time;
        put_goblin(game, gbl, (int)((current_time - last_update) / update_interval) % 4);
        last_update = current_time;

        // Atualize o jogo e renderize o estado atual
        render_game(game);
    }
}
*/
void move_goblin(t_goblin *gbl, int dx, int dy)
{
    if (gbl->is_moving)
        return;

    gbl->dx = dx;                            // Define a direção do movimento no eixo x
    gbl->dy = dy;                            // Define a direção do movimento no eixo y
    gbl->steps_remaining = 10;               // Define o número de passos para completar o movimento
    gbl->step_size = 4;                      // Define o tamanho de cada passo em pixels
    gbl->update_interval = 1000 / 60;        // Define o intervalo de atualização
    gbl->dest_p.x = gbl->gbl_p.x + dx * 20 * 2;  // Calcula a posição de destino no eixo x
    gbl->dest_p.y = gbl->gbl_p.y + dy * 20 * 2;  // Calcula a posição de destino no eixo y
    gbl->last_update_time = clock();         // Define o tempo do último movimento
    gbl->accumulated_time = 0;               // Inicializa o tempo acumulado
    gbl->current_sprite = 0;
    gbl->is_moving = 1;
}

void update_goblin_position(t_goblin *gbl)
{
    if (!gbl) {
        printf("Erro: goblin é NULL\n");
        return;
    }

    clock_t current_time = clock();
    int elapsed_time = (current_time - gbl->last_update_time) * 1000 / CLOCKS_PER_SEC;
    gbl->accumulated_time += elapsed_time;

    // Define a quantidade de tempo que deve acumular para mover um passo
    int time_per_step = gbl->update_interval;

    // Enquanto tivermos acumulado tempo suficiente para pelo menos um passo
    while (gbl->accumulated_time >= time_per_step && gbl->steps_remaining > 0)
    {
        printf("Atualizando posição do goblin: x=%d, y=%d\n", gbl->gbl_p.x, gbl->gbl_p.y);

        // Atualiza a posição do goblin
        gbl->gbl_p.x += gbl->dx * gbl->step_size;
        gbl->gbl_p.y += gbl->dy * gbl->step_size;
        gbl->steps_remaining--;

        printf("Nova posição do goblin: x=%d, y=%d\n", gbl->gbl_p.x, gbl->gbl_p.y);
    //    printf("%d\n", gbl->current_sprite);
        // Atualiza o índice do sprite
        gbl->current_sprite = (gbl->current_sprite + 1) % 3; // Cicla entre 0, 1 e 2

        // Reduz a quantidade de tempo acumulado
        gbl->accumulated_time -= time_per_step;
    }

    // Se o movimento está completo, redefine o índice do sprite para 0
    if (gbl->steps_remaining == 0)
    {
        gbl->is_moving = 0;
        gbl->current_sprite = 0;
    }

    // Atualiza o tempo do último movimento
    gbl->last_update_time = current_time;
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
            if (move_goblins_check(game,cur_gbl, dx, dy))
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

void update_goblin_sprite_randomly(t_game *game)
{
    t_goblin *current_goblin; // Começa com o primeiro goblin na lista
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


/*
void update_all_goblins(t_game *game)
{
    t_goblin *current_goblin = game->gbl; // Começa com o primeiro goblin na lista

    while (current_goblin != NULL)
    {

        // Atualiza o goblin atual
        put_goblin(game, current_goblin, 0);
    //    printf("Gbl X: %d, Gbl Y: %d\n", game->gbl->gbl_p.x, game->gbl->gbl_p.y);
        update_goblin_sprite_randomly(current_goblin);
        // Passa para o próximo goblin na lista
        current_goblin = current_goblin->next;
    }
}
*/