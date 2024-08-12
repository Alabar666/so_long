/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:31:08 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/12 19:58:56 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(int directions[4][2])
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

void	init_game(t_game *game)
{
	game->lst_gbl_upt = time(NULL);
	game->lst_eny_upt = time(NULL);
	game->lst_exit_upt = time(NULL);
	game->global_timer = 0;
	game->is_paused = 0;
	game->wait_input = 0;
	game->run_selected = 0;
}