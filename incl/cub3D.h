#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include <limits.h>
# include "../src/libft/libft.h"
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"

/* screen size */
# define WIDTH 1280
# define HEIGHT 720

/* key hooks */
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.141592653589793

/* map data */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x; // col nbr
    int     player_y; // row nbr
}   t_map;

/* component for input validation */
typedef struct s_component
{
    /* texture and color flags */
    int has_north;
    int has_south;
    int has_west;
    int has_east;
    int has_floor;
    int has_ceiling;
    /* map validation flag */
    int has_map;
    int map_started;
    int empty_after_map;
    int invalid;
    /* player pos */
    int player_x;
    int player_y;
    char    player_dir;
    int     player_count;
    /* map */
    t_map   map;
}   t_component;

/* texture data */
typedef struct s_texture
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     floor_color;
    int     celling_color;
}   t_texture;

/* player data */
typedef struct s_player
{
    float  pos_x;
    float  pos_y;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;

    // double  dir_x;
    // double  dir_y;
}   t_player;

/* game */
typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;

    char *data; // ptr to raw pixel buffer
    int bpp; // bits per pixel (typically 32 for RGBA)
    int size_line; // bytes per row (img width)
    int endian;
    t_player player;
}   t_game;


/* map validation utlis */
char    *ft_strstr(const char *big, char *small);
int is_space(char c);
int is_valid_rgb(char *line);
int check_file_extension(char *filename);
int check_texture_extension(char *texture);

/* map check */
int is_map_line(char *line);
int is_empty_line(char *line);
int is_player(char c);
int validate_map(t_map *map);

/* raycasting */

/* rendering */

/* texture management */

/* utils */

/* player test */
void    init_player(t_player *player);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
void    move_player(t_player * player);

/* main test */
void    cleanup(t_game *game);


#endif