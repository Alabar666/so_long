/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goblin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodev <hugodev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:41:27 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 11:40:29 by hugodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_goblin(t_goblin **head, t_goblin *new_goblin)
{
	t_goblin	*current;

	if (*head == NULL)
	{
		*head = new_goblin;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_goblin;
	}
}

t_goblin	*new_goblin(void)
{
	t_goblin	*new_goblin;

	new_goblin = (t_goblin *)ft_calloc(1, sizeof(t_goblin));
	if (!new_goblin)
	{
		ft_printf("Error allocating memory for a new goblin.\n");
		return (0);
	}
	new_goblin->next = NULL;
	return (new_goblin);
}

void	free_goblins(t_goblin *head)
{
	t_goblin	*current;
	t_goblin	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->gbl);
		free(current);
		current = next;
	}
}

void	put_goblin(t_game *game, t_goblin *goblin, int sprite_index)
{
	char	*current_sprite;
	t_pos	pos;

	pos = goblin->gbl_p;
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
	create_character(goblin->gbl, game, pos.x, pos.y);
	if (goblin->gbl)
		destroy_sprite(&goblin->gbl, game->mlx);
}
