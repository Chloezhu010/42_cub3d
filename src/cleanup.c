#include "../incl/cub3D.h"

/* free the map when error or exit */
void    free_map(t_game *game)
{
    int i;

    if (game->map != NULL)
    {
        i = 0;
        while (i < 11)
        {
            if (game->map[i] != NULL)
                free(game->map[i]);
            i++;
        }
        free(game->map);
        game->map = NULL;
    }
}


/* handle program exit */
void    cleanup(t_game *game)
{
    if (!game)
        return ;
    free_map(game);
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