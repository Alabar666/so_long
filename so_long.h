/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/06/24 18:16:29 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
/*
**                              HEADERS
*/
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include "./Libft/libft.h"
# include <X11/keysym.h>
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
#define MALLOC_ERROR    1
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
typedef struct s_sprite{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    
} t_sprite;

typedef struct s_map{
   char **map;
   int lines;
   int colun;
   int width;
   int height;
}  t_map;

typedef struct s_player{
   int x;
   int y;
   t_sprite *p1;
   int alive;
} t_player;

typedef struct s_game{
   void *mlx;
   void *win;
   t_map map;
   t_sprite *world;
   t_player p1;
   void *e;
   
}  t_game;


/*
**                              FUNCTION PROTOTYPES
*/
char	*get_next_line(int fd);
char	*read_line(int fd, char *backup);
char	*get_line(char *backup);
char	*get_next(char *backup);
size_t	ft_strlen_gnl(char *s);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	*ft_calloc_gnl(size_t count, size_t size);
void	init_map(t_game *game);
int		count_lines(char *file);
void parse_map(char *file, t_game *game);
void map_start(char * file, t_game *game);
void	draw_map(t_game *game);
void	load_images(t_game *game);
int key_pressed(int key, t_game *game);
void clean_img(t_game *game);
int gameover(t_game *game);
char	*get_sprite_path(t_game *game, char c);
void	create_map(t_game *game);
void	put_pixel(t_sprite *sprite, int x, int y, int color);
void    create_world(t_sprite *sprite, t_game *game, int posx, int posy);
t_sprite *create_sprite(t_game *game, char *sprite_path);
unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y);
void	free_map(char **map);
int	update_frame(t_game *game);


#endif
