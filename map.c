/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:07:19 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/12 21:09:33 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void parse_map(const char *map){
    FILE *map = fopen(map, "r");
    if(map == NULL){
        fprintf(stderr, "Erro: Falha ao abrir o arquivo %s\n", map);
        exit(EXIT_FAILURE);
    }






    
}