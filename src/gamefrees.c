/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamefrees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:13:57 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/24 16:43:01 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_all_goblins(t_goblin *goblin_list)
{
	t_goblin	*current;
	t_goblin	*next;

	current = goblin_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_all_enemies(t_enemy *enemy_list)
{
	t_enemy	*current;
	t_enemy	*next;

	current = enemy_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
