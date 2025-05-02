#include "../incl/cub3D.h"

int main(int ac, char **av)
{
    t_map   *map;
    t_game  game;
    t_texture   *texture;
    t_player    *player;

    /* input check */
    if (ac != 2)
    {
        printf("Error\nUsage ./cub3D <map .cub>\n");
        return (1);
    }
    /* map validation */
    // check map's file extension
    if (!check_file_extension(av[1]))
    {
        printf("Error\nFile must be .cub file\n");
        return (1);
    }
    // validate map
    if (!check_input(av[1]))
    {
        printf("Error\nInvalid input\n");
        return (1);
    }

    /* init structure */
    // malloc for the resource
    map = malloc(sizeof(t_map));
    texture = malloc(sizeof(t_texture));
    player = malloc(sizeof(t_player));
    if (!map || !texture || !player)
    {
        printf("Error: Malloc failed\n");
        return (1);
    }
    // init with zero
    ft_memset(map, 0, sizeof(t_map));
    ft_memset(texture, 0, sizeof(t_texture));
    ft_memset(player, 0, sizeof(t_player));

    /* parse map */

    /* print map [DEBUG] */

    /* main game */
    init_game(&game);
    /* key hooks for movement */
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);
    /* click hook for cross-close */
    mlx_hook(game.win, 17, 0, cross_close, &game);
    /* loop */
    mlx_loop_hook(game.mlx, draw_loop, &game);
    mlx_loop(game.mlx);

    /* resource cleanup & exit */

    return (0);
}