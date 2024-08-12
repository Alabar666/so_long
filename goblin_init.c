/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:01:22 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 19:01:25 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_list_goblin(t_game *game)
{
	game->gbl = NULL;
}

void	add_goblin_to_list(t_game *game, int x, int y)
{
	t_goblin	*nw_goblin;
	t_goblin	*current;

	nw_goblin = new_goblin();
	if (!nw_goblin)
	{
		ft_printf("Error creating goblin.\n");
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
			current = current->next;
		current->next = nw_goblin;
	}
}

void	init_goblin(t_goblin *goblin)
{
	int	random_dir;

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
	init_goblin_sprites(goblin);
	random_dir = rand() % 4;
	init_rand_dir_goblin(goblin, random_dir);
}

void	init_goblin_sprites(t_goblin *goblin)
{
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
}

void	init_rand_dir_goblin(t_goblin *goblin, int random_dir)
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
