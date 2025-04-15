#include "../incl/cub3D.h"

int main(int ac, char **av)
{
    t_map   *map;
    t_texture   *texture;
    t_player    *player;

    /* input check */
    if (ac != 2)
    {
        printf("Error: Usage ./cub3D <map .cub>\n");
        return (1);
    }
    /* map validation */
    // check map's file extension
    if (!check_file_extension(av[1]))
    {
        printf("Error: File must be .cub file\n");
        return (1);
    }
    // validate map
    if (!validate_map_file(av[1]))
    {
        printf("Error: Invalid map file\n");
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

    /* main game init */

    /* resource cleanup & exit */

    return (0);
}