/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:55:57 by czhu              #+#    #+#             */
/*   Updated: 2025/05/07 11:00:10 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
}	t_map;

typedef enum s_wall_side
{
	WALL_NORTH,
	WALL_SOUTH,
	WALL_EAST,
	WALL_WEST
}	t_wall_side;

/* component for input validation */
typedef struct s_component
{
	int		has_north;
	int		has_south;
	int		has_west;
	int		has_east;
	int		has_floor;
	int		has_ceiling;
	int		has_map;
	int		map_started;
	int		empty_after_map;
	int		invalid;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		player_count;
	t_map	map;
}	t_component;

/* texture img */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* texture data */
typedef struct s_texture
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	t_img	north_img;
	t_img	south_img;
	t_img	west_img;
	t_img	east_img;
}	t_texture;

/* player data */
typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	float	angle;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

/* game */
typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_player		player;
	t_map			map;
	t_texture		textures;
}	t_game;

typedef struct s_dist_data
{
	float	start_x;
	float	start_y;
	float	end_x;
	float	end_y;
}	t_dist_data;

typedef struct s_render_data
{
	t_wall_side	side;
	float		dist;
	float		height;
	int			start_y;
	int			end;
	t_img		*tex;
	int			tex_x;
	float		step;
	float		tex_pos;
}	t_render_data;

/* input validation*/
int				check_input(char *file_path);
int				add_line_to_map(t_map *map, char *line);
void			check_nswe_texture(char *line, t_component *ctx);

/* input validation utlis */
char			*ft_strstr(const char *big, char *small);
int				is_space(char c);
int				is_valid_rgb(char *line);
int				check_file_extension(char *filename);
int				check_texture_extension(char *texture);

/* map check */
int				is_map_line(char *line);
int				is_empty_line(char *line);
int				is_player(char c);
int				process_player(t_map *map);
int				validate_map(t_map *map);
int				is_map_closed(t_map *map);

/* parsing */
int				parse_input(char *file_path, t_map *map,
					t_texture *texture, t_player *player);
int				parse_rgb(char *line);
int				parse_element_line(char *line, t_texture *texture);
char			*extract_texture_path(char *line);

/* 3D & rendering */
float			fixed_dist(t_dist_data *data, t_game *game);
bool			touch(float px, float py, t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_image(t_game *game);
void			draw_line(t_player *player, t_game *game, float start_x, int i);
int				draw_loop(t_game *game);
t_wall_side		get_wall_side(float ray_x, float ray_y, float dx, float dy);
float			distance(float x, float y);

/* draw_line */
void			draw_ceiling(int i, int start_y, t_game *game);
void			draw_floor(int i, int end, t_game *game);
void			cast_ray(t_player *player, float angle, float *ray_pos);
void			update_ray(float *ray_pos);
int				calc_tex_x(t_wall_side side, float *ray_pos, t_img *tex);

/* texture management */
void			init_img(t_img *img);
int				load_texture(t_game *game, t_img *img, char *path);
int				load_all_textures(t_game *game);
void			cleanup_texture(t_game *game);
int				get_texture_pixel(t_img *img, int x, int y);
t_img			*get_wall_texture(t_game *game, t_wall_side side);

/* player movement */
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move_player(t_player *player, t_game *game);

/* main utils */
void			print_ascii(void);
int				cross_close(t_game *game);
void			init_game(t_game *game);

/* cleanup */
void			free_map(t_map *map);
void			cleanup(t_game *game);

/* debug utils */
void			print_texture(t_texture *texture);
void			print_map(t_map *map);
void			print_player(t_player *player);
int				is_within_bounds(char **grid, int row, int col, int height);

#endif
