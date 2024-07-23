/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/07/23 20:49:47 by hluiz-ma         ###   ########.fr       */
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
    goblin->mv_dir = STAND;
    goblin->current_sprite = 0;

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


void    create_goblin(t_sprite *sprite, t_game *game, int posx, int posy)
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
//                printf("Drawing pixel at (%d, %d) with color %x\n",
//                       posx + x, posy + y, color);
				put_pixel(game->world,
					posx + x,
					posy + y, color);
			}
		}
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
    create_goblin(goblin->gbl, game, x, y);
}

void update_all_goblins(t_game *game)
{
    t_goblin *current_goblin = game->gbl; // Começa com o primeiro goblin na lista
    int sprite_index = 0; // Você pode ajustar isso conforme necessário

    while (current_goblin != NULL)
    {
        // Atualiza o goblin atual
        put_goblin(game, current_goblin, sprite_index);

        // Passa para o próximo goblin na lista
        current_goblin = current_goblin->next;
    }
}