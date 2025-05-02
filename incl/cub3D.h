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
/* map size */
# define BLOCK 64

/* key hooks */
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define PI 3.141592653589793

# define DEBUG 0

/* map data */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x; // col nbr
    int     player_y; // row nbr
}   t_map;

typedef enum {
    WALL_NORTH,
    WALL_SOUTH,
    WALL_EAST,
    WALL_WEST
} t_wall_side;

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

/* 纹理图像数据 */
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

/* texture data */
typedef struct s_texture
{
    char    *north_path;
    char    *south_path;
    char    *west_path;
    char    *east_path;
    int     floor_color;
    int     ceiling_color;
    t_img   north_img;
    t_img   south_img;
    t_img   west_img;
    t_img   east_img;
}   t_texture;

/* player data */
typedef struct s_player
{
    float  pos_x;
    float  pos_y;
    /* for direction movement */
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    /* for rotation */
    float angle;
    bool left_rotate;
    bool right_rotate;
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
    char    **map;
    t_texture textures;
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
void init_img(t_img *img);
int load_texture(t_game *game, t_img *img, char *path);
int load_all_textures(t_game *game);
void cleanup_texture(t_game *game);
int get_texture_pixel(t_img *img, int x, int y);
t_img *get_wall_texture(t_game *game, t_wall_side side);

/* utils */

/* cleanup */
void    cleanup(t_game *game);

/* player test */
void    init_player(t_player *player);
int key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
void    move_player(t_player *player, t_game *game);
bool touch(float px, float py, t_game *game);

/* main test */
void    cleanup(t_game *game);

int get_texture_pixel(t_img *img, int x, int y);

#endif