#include "../incl/cub3D.h"

void    print_texture(t_texture *texture)
{
    printf("north texture: %s\n", texture->north_path);
    printf("south texture: %s\n", texture->south_path);
    printf("west texture: %s\n", texture->west_path);
    printf("east texture: %s\n", texture->east_path);
    printf("floor color: %X\n", texture->floor_color);
    printf("ceiling color: %X\n", texture->ceiling_color);
}

void    print_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            printf("%c", map->grid[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}