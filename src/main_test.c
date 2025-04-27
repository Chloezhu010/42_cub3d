#include "../incl/cub3D.h"

/* initialize map */
char    **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

/* put pixel into the buffer, then display */
void    put_pixel(int x, int y, int color, t_game *game)
{
    int index;
    
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;
    /* cal the exact memory position for the pixel */
    index = y * game->size_line + x * game->bpp / 8;
    /* write color channels: blue, green, red */
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

/* draw a square represents the player */
void    draw_square(int x, int y, int size, int color, t_game *game)
{
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

/* draw the 2D map */
void    draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;

    for (int y = 0; map[y]; y++)
        for (int x = 0; map[y][x]; x++)
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void    init_game(t_game *game)
{
    init_player(&game->player); // init player
    game->map = get_map(); // init map
    /* init mlx, win, data */
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/* helper function for draw_loop */
void    clear_image(t_game *game)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}

int draw_loop(t_game *game)
{
    t_player *player;

    player = &game->player;
    /* player movement control logic */
    move_player(player);
    /* clear the screen */
    clear_image(game);
    /* draw the square */
    draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, game);
    draw_map(game);
    /* put the img to the win */
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

/* handle program exit */
void    cleanup(t_game *game)
{
    if (!game)
        return ;
    //free_map(game);
    if (game->mlx)
	{
		// cleanup_texture(game);
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

/* click cross to close the win */
int	cross_close(t_game *game)
{
	(void)game;
	cleanup(game);
	exit(0);
}

int main(void)
{
    t_game  game;

    init_game(&game);
    /* key hooks for movement */
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);
    /* click hook for cross-close */
    mlx_hook(game.win, 17, 0, cross_close, &game);
    /* loop */
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}