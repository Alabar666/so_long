/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamefrees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:13:57 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 17:30:12 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/**
 * Frees all goblin nodes in a linked list.
 * Iterates through the list and frees each node.
 * 
 * goblin_list A pointer to the head of the goblin linked list.
 */
void	free_all_goblins(t_goblin *goblin_list)
{
	t_goblin	*current;
	t_goblin	*next;

	current = goblin_list;
	while (current)
	{
		next = current->next; // Save the next node
		free(current); // Free the current node
		current = next; // Move to the next node
	}
}

/**
 * Frees all enemy nodes in a linked list.
 * Iterates through the list and frees each node.
 * 
 * enemy_list A pointer to the head of the enemy linked list.
 */
void	free_all_enemies(t_enemy *enemy_list)
{
	t_enemy	*current;
	t_enemy	*next;

	current = enemy_list;
	while (current)
	{
		next = current->next; // Save the next node
		free(current); // Free the current node
		current = next; // Move to the next node
	}
}
