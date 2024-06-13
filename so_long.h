/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/13 21:49:59 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
/*
**                              HEADERS
*/
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>//open
# include <stddef.h>
# include <stdio.h>//error
# include <string.h>//strerror
# include <unistd.h>//read, write
# include <stdlib.h>//malloc,free, exit + rand
/*
**                              BUFFERS
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FDS
#  define MAX_FDS 4242
# endif
/*
**                              KEY CODES
*/
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307

#define SZ 40 //img size
/*
**                              IMAGES
*/
# define FLOOR "./img/floor.xpm"
# define WALL "./img/wall.xpm"
# define BLOOD "./img/blood.xpm"
# define EXIT "./img/ExitPriestess.xpm"

# define PLAYER_FRONT_STAND "./img/gsFront2.xpm"
# define PLAYER_FRONT_MV1 "./img/gsFront1.xpm"
# define PLAYER_FRONT_MV2 "./img/gsFront3.xpm"
# define PLAYER_BACK_MV1 "./img/gsBack1.xpm"
# define PLAYER_BACK_MV2  "./img/gsBack2.xpm"
# define PLAYER_BACK_MV3  "./img/gsBack3.xpm"
# define PLAYER_LEFT_MV1 "./img/gsSideLeft1.xpm"
# define PLAYER_LEFT_MV2  "./img/gsSideLeft2.xpm"
# define PLAYER_LEFT_MV3  "./img/gsSideLeft3.xpm"
# define PLAYER_RIGHT_MV1 "./img/gsSideLeft1.xpm"
# define PLAYER_RIGHT_MV2  "./img/gsSideLeft2.xpm"
# define PLAYER_RIGHT_MV3  "./img/gsSideLeft3.xpm"

# define GOBLIN_FRONT_STAND "./img/GCFront2.xpm"
# define GOBLIN_FRONT_MV1 "./img/GCFront1.xpm"
# define GOBLIN_FRONT_MV2 "./img/GCFront3.xpm"
# define GOBLIN_BACK_MV1 "./img/GCBack1.xpm"
# define GOBLIN_BACK_MV2  "./img/GCBack2.xpm"
# define GOBLIN_BACK_MV3  "./img/GCBack3.xpm"
# define GOBLIN_LEFT_MV1 "./img/GCSideLeft1.xpm"
# define GOBLIN_LEFT_MV2  "./img/GCSideLeft2.xpm"
# define GOBLIN_LEFT_MV3  "./img/GCSideLeft3.xpm"
# define GOBLIN_RIGHT_MV1 "./img/GCSideLeft1.xpm"
# define GOBLIN_RIGHT_MV2  "./img/GCSideLeft2.xpm"
# define GOBLIN_RIGHT_MV3  "./img/GCSideLeft3.xpm"

# define ENEMY_FRONT_STAND "./img/GEnemyFront2.xpm"
# define ENEMY_FRONT_MV1 "./img/GEnemyFront1.xpm"
# define ENEMY_FRONT_MV2 "./img/GEnemyFront3.xpm"
# define ENEMY_BACK_MV1 "./img/GEnemyBack1.xpm"
# define ENEMY_BACK_MV2  "./img/GEnemyBack2.xpm"
# define ENEMY_BACK_MV3  "./img/GEnemyBack3.xpm"
# define ENEMY_LEFT_MV1 "./img/GEnemyLeft1.xpm"
# define ENEMY_LEFT_MV2  "./img/GEnemyLeft2.xpm"
# define ENEMY_LEFT_MV3  "./img/GEnemyLeft3.xpm"
# define ENEMY_RIGHT_MV1 "./img/GEnemyLeft1.xpm"
# define ENEMY_RIGHT_MV2  "./img/GEnemyLeft2.xpm"
# define ENEMY_RIGHT_MV3  "./img/GEnemyLeft3.xpm"
/*
**                              FUNCTION PROTOTYPES
*/
char	*get_next_line(int fd);
char	*read_line(int fd, char *backup);
char	*get_line(char *backup);
char	*get_next(char *backup);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);

#endif