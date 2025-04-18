#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../src/libft/libft.h"
// # include "../minilibx-linux/mlx.h"

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
}   t_component;

/* map data */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x; // col nbr
    int     player_y; // row nbr
}   t_map;

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
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
}   t_player;

/* map validation utlis */
char    *ft_strstr(const char *big, char *small);
int is_space(char c);
int is_valid_rgb(char *line);
int check_file_extension(char *filename);
int check_texture_extension(char *texture);

/* map check */
int is_map_line(char *line);
int is_empty_line(char *line);

/* raycasting */

/* rendering */

/* player control */

/* texture management */

/* utils */

#endif