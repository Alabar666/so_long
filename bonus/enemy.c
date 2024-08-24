/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 16:08:05 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	add_enemy(t_enemy **head, t_enemy *new_enemy)
{
	t_enemy	*current;

	if (*head == NULL)
	{
		*head = new_enemy;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_enemy;
	}
}

void	free_enemys(t_enemy *head)
{
	t_enemy	*current;
	t_enemy	*next;
	int		i;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		i = -1;
		free(current->eny);
		free(current);
		current = next;
	}
}

void	put_enemy(t_game *game, t_enemy *enemy, int sprite_index)
{
	char	*current_sprite;
	t_pos	pos;

	pos = enemy->eny_p;
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
	create_character(enemy->eny, game, pos.x, pos.y);
	if (enemy->eny)
		destroy_sprite(&enemy->eny, game->mlx);
}
