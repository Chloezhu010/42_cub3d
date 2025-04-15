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

typedef struct s_map
{
    char    **grip;
    int     width;
    int     heigth;
}   t_map;

typedef struct s_texture
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     floor_color;
    int     celling_color;
}   t_texture;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
}   t_player;

/* parsing & validation */

/* raycasting */

/* rendering */

/* player control */

/* texture management */

/* utils */

#endif