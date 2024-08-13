/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 19:01:55 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_enemy_to_list(t_game *game, int x, int y)
{
	t_enemy	*nw_enemy;
	t_enemy	*current;

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
			current = current->next;
		current->next = nw_enemy;
	}
}

void	init_enemy(t_enemy *enemy)
{
	int	random_dir;

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
	init_enemy_sprites(enemy);
	random_dir = rand() % 4;
	init_rand_dir_enemy(enemy, random_dir);
}

void	init_enemy_sprites(t_enemy *enemy)
{
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
}

void	init_rand_dir_enemy(t_enemy *enemy, int random_dir)
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

t_enemy	*new_enemy(void)
{
	t_enemy	*new_enemy;

	new_enemy = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
	if (!new_enemy)
	{
		ft_printf("Error allocating memory for a new enemy.\n");
		return (0);
	}
	new_enemy->next = NULL;
	return (new_enemy);
}
