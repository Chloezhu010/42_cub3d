#include "../incl/cub3D.h"

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

void    init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        exit(1);
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
    if (!game->win)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        exit(1);
    }
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        exit(1);
    }
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    if (!game->data)
    {
        mlx_destroy_image(game->mlx, game->img);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        exit(1);
    }
    init_player(&game->player);
}

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
    draw_square(player->pos_y, player->pos_x, 5, 0x00FF00, game);
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
    /* key hooks */
    /* click hook for cross */
    mlx_hook(game.win, 17, 0, cross_close, &game);
    /* loop */
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);
    return (0);
}