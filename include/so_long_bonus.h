/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:13:48 by hluiz-ma          #+#    #+#             */
/*   Updated: 2024/09/15 18:04:36 by hluiz-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
/*
**                              HEADERS
*/
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/keysym.h>
# include <fcntl.h> //open
# include <stddef.h>
# include <stdio.h>  //error
# include <stdlib.h> //malloc,free, exit + rand
# include <string.h> //strerror
# include <time.h>
# include <unistd.h> //read, write
/*
**                              BUFFERS
*/
# define FPS 60
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
# define SPACE 32

# define STAND 0
# define DIR_LEFT 1
# define DIR_RIGHT 2
# define DIR_UP 3
# define DIR_DOWN 4

# define SZ 40 // Size of images in pixels
# define MALLOC_ERROR 1 // Error code for memory allocation failure
# define TRUE 1
# define FALSE 0
# define MAP_ERROR "ERROR\n Provided map is invalid\n"
/*
**                              IMAGES
*/

# define FLOOR "./img/floor.xpm"
# define FLOOR2 "./img/floor2.xpm"
# define FLOOR3 "./img/floor3.xpm"
# define WALL "./img/wall.xpm"
# define WALL2 "./img/wall2.xpm"
# define BLOOD "./img/blood.xpm"
# define BLOOD2 "./img/blood2.xpm"
# define PDEAD "./img/pdead.xpm"

# define CGBLATK "./img/cavernbgatk.xpm"
# define CGBLRUN "./img/cavernbgrun.xpm"
# define CENYATK "./img/cavernbgatkeny.xpm"
# define CENYRUN "./img/cavernbgruneny.xpm"

# define VICTORY1 "./img/victory1.xpm"
# define VICTORY2 "./img/victory2.xpm"
# define VICTORY3 "./img/victory3.xpm"
# define VICTORY4 "./img/victory4.xpm"
# define VICTORY5 "./img/victory5.xpm"
# define VICTORY6 "./img/victory6.xpm"

# define LOSE1 "./img/youdead.xpm"
# define LOSE2 "./img/youdead2.xpm"

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
# define PLAYER_BACK_MV2 "./img/gsBack2.xpm"
# define PLAYER_BACK_MV3 "./img/gsBack3.xpm"
# define PLAYER_LEFT_MV1 "./img/gsSideLeft1.xpm"
# define PLAYER_LEFT_MV2 "./img/gsSideLeft2.xpm"
# define PLAYER_LEFT_MV3 "./img/gsSideLeft3.xpm"
# define PLAYER_RIGHT_MV1 "./img/gsSideRight1.xpm"
# define PLAYER_RIGHT_MV2 "./img/gsSideRight2.xpm"
# define PLAYER_RIGHT_MV3 "./img/gsSideRight3.xpm"
# define PLAYER_BALLOM "./img/ballom.xpm"

# define GOBLIN_FRONT_STAND "./img/GCFront2.xpm"
# define GOBLIN_FRONT_MV1 "./img/GCFront1.xpm"
# define GOBLIN_FRONT_MV2 "./img/GCFront3.xpm"
# define GOBLIN_BACK_MV1 "./img/GCBack1.xpm"
# define GOBLIN_BACK_MV2 "./img/GCBack2.xpm"
# define GOBLIN_BACK_MV3 "./img/GCBack3.xpm"
# define GOBLIN_LEFT_MV1 "./img/GCSideLeft1.xpm"
# define GOBLIN_LEFT_MV2 "./img/GCSideLeft2.xpm"
# define GOBLIN_LEFT_MV3 "./img/GCSideLeft3.xpm"
# define GOBLIN_RIGHT_MV1 "./img/GCSideRight1.xpm"
# define GOBLIN_RIGHT_MV2 "./img/GCSideRight2.xpm"
# define GOBLIN_RIGHT_MV3 "./img/GCSideRight3.xpm"

# define ENEMY_FRONT_STAND "./img/GEnemyFront2.xpm"
# define ENEMY_FRONT_MV1 "./img/GEnemyFront1.xpm"
# define ENEMY_FRONT_MV2 "./img/GEnemyFront3.xpm"
# define ENEMY_BACK_MV1 "./img/GEnemyBack1.xpm"
# define ENEMY_BACK_MV2 "./img/GEnemyBack2.xpm"
# define ENEMY_BACK_MV3 "./img/GEnemyBack3.xpm"
# define ENEMY_LEFT_MV1 "./img/GEnemyLeft1.xpm"
# define ENEMY_LEFT_MV2 "./img/GEnemyLeft2.xpm"
# define ENEMY_LEFT_MV3 "./img/GEnemyLeft3.xpm"
# define ENEMY_RIGHT_MV1 "./img/GEnemyRight1.xpm"
# define ENEMY_RIGHT_MV2 "./img/GEnemyRight2.xpm"
# define ENEMY_RIGHT_MV3 "./img/GEnemyRight3.xpm"
/*
**                              FUNCTION PROTOTYPES
*/

/*
**  STRUCTURE DEFINITIONS
*/

/* Position structure to store coordinates */
typedef struct s_pos
{
	int				x; // x-coordinate
	int				y; // y-coordinate
}					t_pos;

/* Position structure with double precision coordinates */
typedef struct s_pos_double
{
	double			x; // x-coordinate
	double			y; // y-coordinate
}					t_pos_double;

/* Tile structure for map tiles */
typedef struct s_tile
{
	char			type;       // Type of tile (e.g., floor, wall)
	char			*sprt_path; // Path to the sprite image
	t_pos			pos;        // Position of the tile
}					t_tile;

/* Sprite structure for image details */
typedef struct s_sprite
{
	void			*img;           // Pointer to the image
	char			*addr;          // Pointer to the image data
	int				width;         // Width of the image
	int				height;        // Height of the image
	int				bits_per_pixel;// Bits per pixel of the image
	int				line_length;   // Line length of the image data
	int				endian;        // Endianness of the image data
}					t_sprite;

/* Map structure for storing map details */
typedef struct s_map
{
	char			*map_data;  // Map data as a string
	int				lines;      // Number of lines in the map
	int				colun;      // Number of columns in the map
	int				width;      // Width of the map
	int				height;     // Height of the map
	t_pos			start_p1_p; // Starting position of player 1
	int				goblin;     // Number of goblins
	int				enemy;      // Number of enemies
	int				exit;       // Number of exits
	int				player;     // Number of players
	t_tile			**map;       // 2D array of map tiles
}					t_map;

// Player structure holding information about the player character
typedef struct s_player
{
    t_pos            p1_p;                   // Position of the player
    t_sprite         *p1;                    // Player sprite
    t_sprite         *bl;                    // Balloon sprite (for exit animation)
    int              alive;                  // Status indicating if the player is alive (1 if alive, 0 otherwise)
    int              mv_dir;                 // Current movement direction of the player
    int              moves;                  // Number of moves made by the player
    int              is_moving;              // Flag indicating if the player is currently moving (1 if moving, 0 otherwise)
    int              current_sprite;         // Index of the current sprite used for animation
    char             *pl_ballom;             // Path to the balloon sprite image (for exit animation)
    char             *front_sprites[3];     // Array of sprite paths for player facing forward
    char             *back_sprites[3];      // Array of sprite paths for player facing backward
    char             *left_sprites[3];      // Array of sprite paths for player facing left
    char             *right_sprites[3];     // Array of sprite paths for player facing right
    t_pos            dest_p;                 // Destination position for movement
    int              dx;                     // Delta x for movement
    int              dy;                     // Delta y for movement
    int              steps_remaining;        // Number of steps remaining to reach the destination
    int              step_size;              // Size of each step during movement
    int              update_interval;        // Time interval between updates (for movement animation)
    int              accumulated_time;       // Accumulated time for animation updates
    clock_t          last_update_time;       // Time of the last update for animation purposes
}                   t_player;

// Goblin structure holding information about the goblin enemy
typedef struct s_goblin
{
    t_pos            gbl_p;                  // Position of the goblin
    t_sprite         *gbl;                   // Goblin sprite
    int              mv_dir;                 // Current movement direction of the goblin
    int              current_sprite;         // Index of the current sprite used for animation
    char             *front_sprites[3];     // Array of sprite paths for goblin facing forward
    char             *back_sprites[3];      // Array of sprite paths for goblin facing backward
    char             *left_sprites[3];      // Array of sprite paths for goblin facing left
    char             *right_sprites[3];     // Array of sprite paths for goblin facing right
    char             *dead;                  // Path to the dead goblin sprite image
    int              is_alive;               // Flag indicating if the goblin is alive (1 if alive, 0 otherwise)
    int              is_moving;             // Flag indicating if the goblin is currently moving (1 if moving, 0 otherwise)
    t_pos            dest_p;                 // Destination position for movement
    int              dx;                     // Delta x for movement
    int              dy;                     // Delta y for movement
    int              steps_remaining;        // Number of steps remaining to reach the destination
    int              step_size;              // Size of each step during movement
    int              update_interval;        // Time interval between updates (for movement animation)
    int              accumulated_time;       // Accumulated time for animation updates
    clock_t          last_update_time;       // Time of the last update for animation purposes
    struct s_goblin  *next;                  // Pointer to the next goblin in the list (for linked list of goblins)
}                   t_goblin;

// Enemy structure holding information about generic enemies in the game
typedef struct s_enemy
{
    t_pos            eny_p;                  // Position of the enemy
    t_sprite         *eny;                   // Enemy sprite
    int              mv_dir;                 // Current movement direction of the enemy
    int              current_sprite;         // Index of the current sprite used for animation
    char             *front_sprites[3];     // Array of sprite paths for enemy facing forward
    char             *back_sprites[3];      // Array of sprite paths for enemy facing backward
    char             *left_sprites[3];      // Array of sprite paths for enemy facing left
    char             *right_sprites[3];     // Array of sprite paths for enemy facing right
    char             *dead;                  // Path to the dead enemy sprite image
    int              is_alive;               // Flag indicating if the enemy is alive (1 if alive, 0 otherwise)
    int              is_moving;             // Flag indicating if the enemy is currently moving (1 if moving, 0 otherwise)
    t_pos            dest_p;                 // Destination position for movement
    int              dx;                     // Delta x for movement
    int              dy;                     // Delta y for movement
    int              steps_remaining;        // Number of steps remaining to reach the destination
    int              step_size;              // Size of each step during movement
    int              update_interval;        // Time interval between updates (for movement animation)
    int              accumulated_time;       // Accumulated time for animation updates
    clock_t          last_update_time;       // Time of the last update for animation purposes
    struct s_enemy   *next;                  // Pointer to the next enemy in the list (for linked list of enemies)
}                   t_enemy;

// Exit structure holding information about the exit point in the game
typedef struct s_exit
{
    t_pos            ex_p;                   // Position of the exit
    t_sprite         *ex1;                   // Exit sprite
    t_sprite         *bl;                    // Balloon sprite (for exit animation)
    int              current_sprite;         // Index of the current sprite used for animation
    char             *exit_sprites[4];      // Array of sprite paths for different exit animations
    char             *exit_ballom[4];       // Array of paths for different balloon images used in exit animation
}                   t_exit;

// Battle structure holding information about the battle screen and related assets
typedef struct s_battle
{
    t_sprite         *btl_img;               // Battle background image or sprite
    char             *gatk_path;             // Path to the player's attack animation or sprite
    char             *grun_path;             // Path to the player's grunt animation or sprite
    char             *eatk_path;             // Path to the enemy's attack animation or sprite
    char             *erun_path;             // Path to the enemy's run animation or sprite
    int              is_running;             // Flag indicating if the battle is currently running (1 if running, 0 otherwise)
    char             enemy_type;             // Type of enemy currently engaged in battle
}                   t_battle;

// Game structure holding the core elements and state of the game
typedef struct s_game
{
    void            *mlx;                    // Pointer to the MiniLibX graphics library instance
    void            *win;                    // Pointer to the game window created with MiniLibX
    t_map            map;                    // Map structure containing the game map data and related functions
    t_sprite        *world;                  // Pointer to the world sprite or background image
    t_sprite        *end_img;                // Pointer to the end game screen image
    t_player        p1;                     // Player structure containing player-specific data and state
    t_goblin        *gbl;                    // Pointer to the linked list of goblin enemies
    t_enemy         *eny;                    // Pointer to the linked list of generic enemies
    t_exit          ext;                    // Exit structure containing data related to the exit point
    t_battle        battle;                 // Battle structure containing data and assets for battles
    time_t          lst_gbl_upt;            // Timestamp of the last goblin update
    time_t          lst_eny_upt;            // Timestamp of the last enemy update
    time_t          lst_exit_upt;           // Timestamp of the last exit update
    unsigned long   global_timer;           // Global timer for managing various timed events
    int             sprite_index;           // Index of the currently active sprite
    int             is_paused;              // Flag indicating if the game is currently paused (1 if paused, 0 otherwise)
    int             wait_input;            // Flag indicating if the game is waiting for player input (1 if waiting, 0 otherwise)
    int             run_selected;          // Flag indicating if the run option is selected (1 if selected, 0 otherwise)
    int             show_end_screen;       // Flag indicating if the end game screen should be shown (1 if shown, 0 otherwise)
    unsigned long   message_display_duration; // Duration for which messages are displayed on the screen
}                   t_game;

/*
**                              FUNCTION PROTOTYPES
*/
// MAP

// Creates the map based on the game's data
void create_map(t_game *game);

// Initializes map by reading from a file and setting up necessary data
void map_start(char *file, t_game *game);

// Allocates memory for the map data structures
void map_malloc(t_game *game);

// Fills the map with tile data from the loaded map file
void fill_map(t_game *game);

// Draws the map onto the game window
void draw_map(t_game *game);

// Initializes the map by setting up initial values and parameters
void init_map(t_game *game);

// Counts the number of lines in the map file
int count_lines(char *file);

// Reads the map file and initializes the map structure
void read_map(char *file, t_game *game);

// Opens the map file and returns a file descriptor
int open_map_file(const char *file);

// Creates a new world object in the game with the given sprite and position
void create_world(t_sprite *sprite, t_game *game, int posx, int posy);

// Concatenates two strings and returns the result
char *ft_strcat(char *dest, const char *src);

// Creates a new tile with the specified type and position
t_tile new_type(char type, int x, int y);

// Puts the entire map on the game window
void put_map(t_game *game);

// Puts a specific tile at the given position on the game window
void put_tile(t_game *game, int x, int y);

// Renders the game elements on the screen
void render_game(t_game *game);

// EXIT

// Initializes exit-related game elements
void init_exit(t_game *game);

// Creates an exit object in the game with the given sprite and position
void create_exit(t_sprite *sprite, t_game *game, int posx, int posy);

// Puts the exit on the game window
void put_exit(t_game *game);

// MAP CHECKS

// Performs various checks on the map to ensure its validity
void map_checks(t_game *game);

// Checks if the map has walls and returns 1 if valid, 0 otherwise
int check_wall(t_map map);

// Checks if the map is rectangular
int is_map_rectangular(t_map *map);

// Checks if the map size exceeds the maximum allowed size
int map_max_size_check(t_game *game, t_map *map);

// Checks if the map file has a valid extension
int check_file_ext(const char *file);

// Checks the type of tile at the specified position in the map
void check_type(t_game *game, char type, int x, int y);

// Checks if the map meets the conditions to win the game
int check_map_winability(t_game *game);

// Duplicates the map of tiles for processing or comparison
t_tile **duplicate_tile_map(t_tile **map, int lines, int colun);

// Explores the map starting from the given coordinates
void explore_map(t_game *game, t_tile **map, int x, int y);

// Checks the characters in the map for validity
int map_caracter(t_game *game);

// SPRITE

// Loads all required images for the game
void load_images(t_game *game);

// Cleans up image resources
void clean_img(t_game *game);

// Gets the path of the sprite image based on the character type
char *get_sprite_path(t_game *game, char c);

// Puts a pixel of a specific color in the sprite image
void put_pixel(t_sprite *sprite, int x, int y, int color);

// Creates a new sprite object from the specified image path
t_sprite *create_sprite(t_game *game, char *sprite_path);

// Gets the color of a pixel in the sprite image
unsigned int get_color_in_pixel(t_sprite *sprite, int x, int y);

// Puts the player sprite at the specified index in the game window
void put_player(t_game *game, int sprite_index);

// Creates a new character sprite with the given position
void create_character(t_sprite *sprite, t_game *game, int posx, int posy);

// Gets the path of the player sprite image based on the character type
char *get_player_path(t_game *game, char c);

// Initializes the player sprites
void init_player(t_game *game);

// Resizes the combat screen sprite
void resize_combat(t_game *game, t_sprite *resized_combat);

// RENDER

// Renders the background image of the game window
void render_background(t_game *game);

// Renders all goblins on the game window
void render_goblins(t_game *game);

// Renders all enemies on the game window
void render_enemies(t_game *game);

// Renders the player and any additional elements (e.g., collectables)
void render_player_and_extras(t_game *game);

// Moves game elements randomly, such as goblins and enemies
void move_randomly(t_game *game);

// Updates the positions of game elements
void update_positions(t_game *game);

// Updates game elements based on time since the last update
void update_game_elements(t_game *game, clock_t *last_time);

// Updates the game frame
int update_frame(t_game *game);

// PLAYER

// Initializes player sprites for rendering
void init_player_sprites(t_game *game);

// GOBLINS

// Initializes a goblin object
void init_goblin(t_goblin *goblin);

// Initializes goblin sprites for rendering
void init_goblin_sprites(t_goblin *goblin);

// Adds a goblin to the game at the specified position
void add_goblin_to_list(t_game *game, int x, int y);

// Creates a new goblin object with the given sprite and position
void create_goblin(t_sprite *sprite, t_game *game, int posx, int posy);

// Puts a goblin sprite at the specified index in the game window
void put_goblin(t_game *game, t_goblin *goblin, int sprite_index);

// Updates all goblins in the game
void update_all_goblins(t_game *game);

// Frees the memory allocated for goblins
void free_goblins(t_goblin *head);

// Creates a new goblin object and returns it
t_goblin *new_goblin(void);

// Initializes the goblin list for the game
void init_list_goblin(t_game *game);

// Initializes random direction for a goblin
void init_rand_dir_goblin(t_goblin *goblin, int random_dir);

// Moves goblins randomly
void move_rand_goblins(t_game *game);

// Initializes possible directions for goblins to move
void init_directions(int directions[4][2]);

// Updates the goblin sprite randomly
void update_goblin_sprite_randomly(t_game *game);

// Checks if goblins can move to a new position
int move_goblins_check(t_game *game, t_goblin *eny, int dx, int dy);

// ENEMIES

// Initializes an enemy object
void init_enemy(t_enemy *enemy);

// Initializes enemy sprites for rendering
void init_enemy_sprites(t_enemy *enemy);

// Adds an enemy to the game at the specified position
void add_enemy_to_list(t_game *game, int x, int y);

// Creates a new enemy object with the given sprite and position
void create_enemy(t_sprite *sprite, t_game *game, int posx, int posy);

// Puts an enemy sprite at the specified index in the game window
void put_enemy(t_game *game, t_enemy *enemy, int sprite_index);

// Updates all enemies in the game
void update_all_enemys(t_game *game);

// Frees the memory allocated for enemies
void free_enemys(t_enemy *head);

// Creates a new enemy object and returns it
t_enemy *new_enemy(void);

// Initializes the enemy list for the game
void init_list_enemy(t_game *game);

// Initializes random direction for an enemy
void init_rand_dir_enemy(t_enemy *enemy, int random_dir);

// Moves enemies randomly
void move_rand_enemys(t_game *game);

// Updates the enemy sprite randomly
void update_enemy_sprite_randomly(t_game *game);

// Checks if enemies can move to a new position
int move_enemys_check(t_game *game, t_enemy *gbl, int dx, int dy);

// UTILS

// Handles the game loop hook, called periodically by the game loop
int game_loop_hook(t_game *game);

// Initializes the game with necessary data and settings
void init_game(t_game *game);

// Creates the end screen after the game ends
void create_end_screen(t_game *game);

// Ends the game and performs necessary cleanup
void end_game(t_game *game);

// Renders the end screen of the game
void render_end_screen(t_game *game);

// Resizes the end screen sprite and updates its image path
void resize_end(t_game *game, t_sprite *resized_end, char *image_path);

// Puts the "game over" image on the game window
void put_dead(t_game *game);

// Resizes the end screen text sprite
void resize_end_text(t_sprite *dest, t_sprite *src);

// Animates the end screen with victory or defeat animations
void animate_end_screen(t_game *game);

// Initializes end screen images
void initialize_end_images(char *images[]);

// MOVES

// Handles key presses for player controls
int key_pressed(int key, t_game *game);

// Handles battle-related key presses
int handle_battle_keys(int key, t_game *game);

// Handles player movement based on key presses
int handle_player_movement(int key, t_game *game);

// Moves the player by a specified amount
void move_player(t_game *game, int dx, int dy);

// Updates player movements and actions
void player_mov(t_game *game);

// Moves the player based on the current direction
void move_dir(t_game *game);

// Updates the player's animation frame
int update_player_frame(t_game *game);

// Moves a goblin by a specified amount
void move_goblin(t_game *game, t_goblin *gbl, int dx, int dy);

// Moves an enemy by a specified amount
void move_enemy(t_game *game, t_enemy *eny, int dx, int dy);

// Updates the player's position based on movement
void update_player_position(t_game *game);

// Updates the position of a goblin
void update_goblin_position(t_goblin *gbl);

// Updates the position of an enemy
void update_enemy_position(t_enemy *eny);

// Puts the current moves on the game window
void put_moves(t_game *game);

// Updates the map tiles based on player movements
void update_map_tiles(t_game *game, t_pos old_pos, t_pos new_pos, char type);

// Checks the player's new position and handles interactions
void check_position(t_game *game, int dx, int dy);

// Handles interactions with enemies and checks for victory conditions
void handle_enemies_and_victory(t_game *game, int dx, int dy);

// Handles interactions with goblins and checks for game state updates
void handle_goblins(t_game *game, int dx, int dy);

// Checks for overlapping positions between game elements
void check_for_overlap(t_game *game);

// BATTLE

// Initializes battle mode and related elements
void init_battle(t_game *game);

// Starts a battle with the specified enemy type
void start_battle(t_game *game, char enemy_type);

// Creates the battle-related sprite objects
void create_battle(t_sprite *sprite, t_game *game);

// Creates the battle screen with necessary elements
void create_battle_screen(t_game *game);

// Handles key presses during a battle
void battle_keys(int key, t_game *game);

// Handles the battle loop hook, called periodically during battle
int battle_loop_hook(t_game *game);

// Closes the battle screen and performs necessary cleanup
void close_battle(t_game *game);

// Loads battle-related resources
void battle_load(t_game *game);

// Destroys a sprite and cleans up its resources
void destroy_sprite(t_sprite **sprite, void *mlx);

// FREE EXIT

// Handles game over conditions and performs cleanup
int gameover(t_game *game);

// Frees all goblins and their resources
void free_all_goblins(t_goblin *goblin_list);

// Frees all enemies and their resources
void free_all_enemies(t_enemy *enemy_list);

// Frees the map and its associated resources
void free_map(t_map *map);

// Frees the tile map and its resources
void free_tile_map(t_tile **tile_map, int lines, int colun);

// Frees MiniLibX resources
void free_mlx(t_game *game);

// Handles game errors and performs cleanup
void game_error(int fd, t_game *game);

#endif
