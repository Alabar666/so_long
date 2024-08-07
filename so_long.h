/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/08/05 19:24:48 by hluiz-ma         ###   ########.fr       */
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
# include <time.h>
/*
**                              BUFFERS
*/
#define FRAME_DURATION  (CLOCKS_PER_SEC / 60)
#define INTEVAL (1.0 / FPS)
#define FPS 60
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
# define ENTER 65293

# define STAND       0
# define DIR_LEFT    1
# define DIR_RIGHT   2
# define DIR_UP      3
# define DIR_DOWN    4 

# define SZ 40 //img size
# define MALLOC_ERROR    1
# define TRUE 1
# define FALSE 0
# define MAP_ERROR "ERROR\n Provided map is invalid\n"
/*
**                              IMAGES
*/

# define START "./img/p1start.xpm"
# define FLOOR "./img/floor.xpm"
# define FLOOR2 "./img/floor2.xpm"
# define FLOOR3 "./img/floor3.xpm"
# define WALL "./img/wall.xpm"
# define WALL2 "./img/wall2.xpm"
# define BLOOD "./img/blood.xpm"
# define BLOOD2 "./img/blood2.xpm"

# define COMBAT "./img/combatscrenn630x500.xpm"
# define CPLAYER "./img/player150.xpm"
# define CGOBLIN "./img/goblin150.xpm"
# define CENEMY "./img/enemy150.xpm"
# define CSATACK "./img/atack.xpm"
# define CSRUN "./img/run75.xpm"
# define CATACK "./img/atack1.xpm"
# define CRUN "./img/run1.xpm"

# define EXIT_FRONT "./img/prissfront.xpm"
# define EXIT_BACK "./img/prissback.xpm"
# define EXIT_LEFT "./img/prissleft.xpm"
# define EXIT_RIGHT "./img/prissright.xpm"

# define EXIT_BSAD "./img/sad.xpm"
# define EXIT_BFEAR "./img/fear.xpm"
# define EXIT_BCRY "./img/cry.xpm"
# define EXIT_BHELP "./img/help.xpm"

# define PLAYER_FRONT_STAND "./img/gsFront2.xpm"
# define PLAYER_FRONT_MV1 "./img/gsFront1.xpm"
# define PLAYER_FRONT_MV2 "./img/gsFront3.xpm"
# define PLAYER_BACK_MV1 "./img/gsBack1.xpm"
# define PLAYER_BACK_MV2  "./img/gsBack2.xpm"
# define PLAYER_BACK_MV3  "./img/gsBack3.xpm"
# define PLAYER_LEFT_MV1 "./img/gsSideLeft1.xpm"
# define PLAYER_LEFT_MV2  "./img/gsSideLeft2.xpm"
# define PLAYER_LEFT_MV3  "./img/gsSideLeft3.xpm"
# define PLAYER_RIGHT_MV1 "./img/gsSideRight1.xpm"
# define PLAYER_RIGHT_MV2  "./img/gsSideRight2.xpm"
# define PLAYER_RIGHT_MV3  "./img/gsSideRight3.xpm"
# define PLAYER_BALLOM  "./img/ballom.xpm"

# define GOBLIN_FRONT_STAND "./img/GCFront2.xpm"
# define GOBLIN_FRONT_MV1 "./img/GCFront1.xpm"
# define GOBLIN_FRONT_MV2 "./img/GCFront3.xpm"
# define GOBLIN_BACK_MV1 "./img/GCBack1.xpm"
# define GOBLIN_BACK_MV2  "./img/GCBack2.xpm"
# define GOBLIN_BACK_MV3  "./img/GCBack3.xpm"
# define GOBLIN_LEFT_MV1 "./img/GCSideLeft1.xpm"
# define GOBLIN_LEFT_MV2  "./img/GCSideLeft2.xpm"
# define GOBLIN_LEFT_MV3  "./img/GCSideLeft3.xpm"
# define GOBLIN_RIGHT_MV1 "./img/GCSideRight1.xpm"
# define GOBLIN_RIGHT_MV2  "./img/GCSideRight2.xpm"
# define GOBLIN_RIGHT_MV3  "./img/GCSideRight3.xpm"

# define ENEMY_FRONT_STAND "./img/GEnemyFront2.xpm"
# define ENEMY_FRONT_MV1 "./img/GEnemyFront1.xpm"
# define ENEMY_FRONT_MV2 "./img/GEnemyFront3.xpm"
# define ENEMY_BACK_MV1 "./img/GEnemyBack1.xpm"
# define ENEMY_BACK_MV2  "./img/GEnemyBack2.xpm"
# define ENEMY_BACK_MV3  "./img/GEnemyBack3.xpm"
# define ENEMY_LEFT_MV1 "./img/GEnemyLeft1.xpm"
# define ENEMY_LEFT_MV2  "./img/GEnemyLeft2.xpm"
# define ENEMY_LEFT_MV3  "./img/GEnemyLeft3.xpm"
# define ENEMY_RIGHT_MV1 "./img/GEnemyRight1.xpm"
# define ENEMY_RIGHT_MV2  "./img/GEnemyRight2.xpm"
# define ENEMY_RIGHT_MV3  "./img/GEnemyRight3.xpm"
/*
**                              FUNCTION PROTOTYPES
*/
typedef struct s_pos{
    int x;
    int y;
    
} t_pos;

typedef struct s_tile{
   char type;
   char *sprt_path;
   t_pos pos;
    
} t_tile;

typedef struct s_sprite{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
    
} t_sprite;

typedef struct s_map
{
   char *map_data;
   int lines;
   int colun;
   int width;
   int height;
   t_pos start_p1_p;
   int goblin;
   int enemy;
   int exit;
   int player;
   t_tile **map;   
}  t_map;

typedef struct s_player
{
   t_pos p1_p;
   t_sprite *p1;
   t_sprite *bl;
   int alive;
   int mv_dir;
   int moves;
   int is_moving;
   int current_sprite;
   char *pl_ballom;
   char *front_sprites[3];
   char *back_sprites[3];  
   char *left_sprites[3];  
   char *right_sprites[3];
   t_pos dest_p;
   int dx;
   int dy;
   int steps_remaining;
   int step_size;
   int update_interval; 
   int accumulated_time;
   clock_t last_update_time; 
} t_player;

typedef struct s_goblin{
   t_pos gbl_p;
   t_sprite *gbl;
   int mv_dir;
   int current_sprite;
   char *front_sprites[3];
   char *back_sprites[3];  
   char *left_sprites[3];  
   char *right_sprites[3];
   char *dead;
   int is_alive;
   int is_moving;
   t_pos dest_p;
   int dx;
   int dy;
   int steps_remaining;
   int step_size;
   int update_interval;
   int accumulated_time;
   clock_t last_update_time; 
   struct s_goblin *next;     
} t_goblin;

typedef struct s_enemy{
   t_pos eny_p;
   t_sprite *eny;
   int mv_dir;
   int current_sprite;
   char *front_sprites[3];
   char *back_sprites[3];  
   char *left_sprites[3];  
   char *right_sprites[3];
   char *dead;
   int is_alive;
   int is_moving;
   t_pos dest_p;
   int dx;
   int dy;
   int steps_remaining;
   int step_size;
   int update_interval;
   int accumulated_time;
   clock_t last_update_time; 
   struct s_enemy *next;     
} t_enemy;

typedef struct s_exit{
   t_pos ex_p;
   t_sprite *ex1;
   t_sprite *bl;
   int current_sprite;
   char *exit_sprites[4];
   char *exit_ballom[4];
} t_exit;


typedef struct s_battle{
   t_sprite *btl_img;
   t_sprite *btl_p1;
   t_sprite *btl_gbl;
   t_sprite *btl_eny;
   t_sprite *batk;
   t_sprite *brun;
   char *p1_sprt;
   char *gbl_sprt;
   char *eny_sprt;
   char *atk_sprt;
   char *run_sprt;
   int is_running;
}  t_battle;

typedef struct s_game{
   void *mlx;
   void *win;
   t_map map;
   t_sprite *world;
   t_player p1;
   t_goblin *gbl;
   t_enemy *eny;      
   t_exit ext;
   t_battle battle;
   time_t lst_gbl_upt;
   time_t lst_eny_upt;
   time_t lst_exit_upt;
   unsigned long global_timer;
   void *e;
   int sprite_index;
   int is_paused;   
}  t_game;

/*
**                              FUNCTION PROTOTYPES
*/

//MAP
void	create_map(t_game *game);
void map_start(char * file, t_game *game);
void map_malloc(t_map *map);
void fill_map(t_game *game);
void	draw_map(t_game *game);
void	init_map(t_game *game, int is_init);
int		count_lines(char *file);
void read_map(char *file, t_game *game);
void    create_world(t_sprite *sprite, t_game *game, int posx, int posy);
char *ft_strcat(char *dest, const char* src);
t_tile	new_type(char type, int x, int y);
void	free_map(t_tile **map);
void	game_error(int fd, t_map *map, char *error);
void	put_map(t_game *game);
void	put_tile(t_game *game, int x, int y);

void render_game(t_game *game);


// exit
void init_exit(t_game *game);
void create_exit(t_sprite *sprite, t_game *game, int posx, int posy);
void	put_exit(t_game *game);

// map checks
void map_checks(t_game *game);
int check_wall(t_map map);
int is_map_rectangular(t_map *map);
int map_max_size_check(t_game *game,t_map *map);
int check_file_ext(char *file);
void check_type(t_game *game, char type, int x, int y);


//sprite
void	load_images(t_game *game);
void clean_img(t_game *game);
char	*get_sprite_path(t_game *game, char c);
void	put_pixel(t_sprite *sprite, int x, int y, int color);
t_sprite *create_sprite(t_game *game, char *sprite_path);
unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y);
int	update_frame(void *param);
void	put_player(t_game *game, int sprite_index);
void    create_character(t_sprite *sprite, t_game *game, int posx, int posy);
char	*get_player_path(t_game *game, char c);
void init_player(t_game *game);

//goblins
void init_goblin(t_goblin *goblin);
void add_goblin_to_list(t_game *game, int x, int y);
void    create_goblin(t_sprite *sprite, t_game *game, int posx, int posy);
void	put_goblin(t_game *game, t_goblin *goblin, int sprite_index);
void update_all_goblins(t_game *game);
void free_goblins(t_goblin *head);
t_goblin *new_goblin(void);
void init_list_goblin(t_game *game);
void init_rand_dir_goblin(t_goblin *goblin, int random_dir);
void move_rand_goblins(t_game *game);
void init_directions(int directions[4][2]);
void update_goblin_sprite_randomly(t_game *game);
int move_goblins_check(t_game *game, t_goblin *eny, int dx, int dy);

//enemys
void init_enemy(t_enemy *enemy);
void add_enemy_to_list(t_game *game, int x, int y);
void    create_enemy(t_sprite *sprite, t_game *game, int posx, int posy);
void	put_enemy(t_game *game, t_enemy *enemy, int sprite_index);
void update_all_enemys(t_game *game);
void free_enemys(t_enemy *head);
t_enemy *new_enemy(void);
void init_list_enemy(t_game *game);
void init_rand_dir_enemy(t_enemy *enemy, int random_dir);
void move_rand_enemys(t_game *game);
void init_directions(int directions[4][2]);
void update_enemy_sprite_randomly(t_game *game);
int move_enemys_check(t_game *game, t_enemy *gbl, int dx, int dy);

// utils
int check_file_ext(char *file);


//moves
int key_pressed(int key, t_game *game);
void move_player(t_game *game, int dx, int dy);
void player_mov(t_game *game);
void	move_dir(t_game *game);
int	update_player_frame(t_game *game);
void move_goblin(t_game *game, t_goblin *gbl, int dx, int dy);
void move_enemy(t_game *game, t_enemy *eny, int dx, int dy);
void update_player_position(t_game *game);
void update_goblin_position(t_goblin *gbl);
void update_enemy_position(t_enemy *eny);
void put_moves(t_game *game);
void update_map_tiles(t_game *game, int old_x, int old_y, int new_x, int new_y, char type);
void check_position(t_game *game, int dx, int dy);

//battle
void init_battle(t_game *game);
void start_battle(t_game *game);
void    create_battle(t_sprite *sprite, t_game *game);
void	create_battle_screen(t_game *game);
void render_battle(t_game *game);

//free exit
int gameover(t_game *game);




#endif
