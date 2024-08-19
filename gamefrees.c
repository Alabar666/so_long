/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamefrees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:13:57 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/19 19:18:07 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	free_goblin_sprites(t_goblin *goblin)
{
	int	i;

	if (goblin->dead)
		free(goblin->dead);
	i = -1;
	while (++i < 3)
	{
		if (goblin->front_sprites[i])
			free(goblin->front_sprites[i]);
		if (goblin->back_sprites[i])
			free(goblin->back_sprites[i]);
		if (goblin->left_sprites[i])
			free(goblin->left_sprites[i]);
		if (goblin->right_sprites[i])
			free(goblin->right_sprites[i]);
	}
}

void	free_enemy_sprites(t_enemy *enemy)
{
	int	i;

	if (enemy->dead)
		free(enemy->dead);
	i = -1;
	while (++i < 3)
	{
		if (enemy->front_sprites[i])
			free(enemy->front_sprites[i]);
		if (enemy->back_sprites[i])
			free(enemy->back_sprites[i]);
		if (enemy->left_sprites[i])
			free(enemy->left_sprites[i]);
		if (enemy->right_sprites[i])
			free(enemy->right_sprites[i]);
	}
}

void	free_player_sprites(t_player *player)
{
	int	i;

	if (player->pl_ballom)
		free(player->pl_ballom);
	i = -1;
	while (++i < 3)
	{
		if (player->front_sprites[i])
			free(player->front_sprites[i]);
		if (player->back_sprites[i])
			free(player->back_sprites[i]);
		if (player->left_sprites[i])
			free(player->left_sprites[i]);
		if (player->right_sprites[i])
			free(player->right_sprites[i]);
	}
}

void	free_exit_sprites(t_exit *exit)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (exit->exit_sprites[i])
			free(exit->exit_sprites[i]);
		if (exit->exit_ballom[i])
			free(exit->exit_ballom[i]);
	}
}

void	free_all_goblins(t_goblin *goblin_list)
{
	t_goblin	*current;
	t_goblin	*next;

	current = goblin_list;
	while (current)
	{
		next = current->next;
		free_goblin_sprites(current);
		free(current);
		current = next;
	}
}

void	free_all_enemies(t_enemy *enemy_list)
{
	t_enemy *current;
	t_enemy *next;

	current = enemy_list;
	while (current)
	{
		next = current->next;
		free_enemy_sprites(current);
		free(current);
		current = next;
	}
}
