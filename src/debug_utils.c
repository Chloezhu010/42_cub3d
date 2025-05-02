#include "../incl/cub3D.h"

void    print_texture(t_texture *texture)
{
    printf("north texture: %s\n", texture->north);
    printf("south texture: %s\n", texture->south);
    printf("west texture: %s\n", texture->west);
    printf("east texture: %s\n", texture->east);
    printf("floor color: %X\n", texture->floor_color);
    printf("ceiling color: %X\n", texture->ceiling_color);
}