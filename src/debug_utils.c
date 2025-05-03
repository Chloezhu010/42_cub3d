#include "../incl/cub3D.h"

void    print_texture(t_texture *texture)
{
    printf("=== texture info ===\n");
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

    printf("=== map info ===\n");
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
    printf("map height: %d\n", map->height);
    printf("map width: %d\n", map->width);
    printf("map player x: %d\n", map->player_x);
    printf("map player y: %d\n", map->player_y);
}

void    print_player(t_player *player)
{
    printf("=== player info ===\n");
    printf("player pos x: %f\n", player->pos_x);
    printf("player pos y: %f\n", player->pos_y);
    printf("player angle: %f * PI\n", player->angle / PI);
    // printf("player key up: %d\n", player->key_up);
    // printf("player key up: %d\n", player->key_down);
    // printf("player key up: %d\n", player->key_left);
    // printf("player key up: %d\n", player->key_right);
    // printf("player key up: %d\n", player->left_rotate);
    // printf("player key up: %d\n", player->right_rotate);
}