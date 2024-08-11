/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:31:08 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/09 16:31:09 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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