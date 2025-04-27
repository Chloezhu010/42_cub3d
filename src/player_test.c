#include "../incl/cub3D.h"

void    init_player(t_player *player)
{
    player->pos_x = HEIGHT / 2;
    player->pos_y = WIDTH / 2;
    player->angle = PI / 2; // initial angle

    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;

    player->left_rotate = false;
    player->right_rotate = false;
}

int key_press(int keycode, t_game *game)
{
    t_player *player = &game->player;
    
    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;
    if (keycode == LEFT)
        player->left_rotate = true;
    if (keycode == RIGHT)
        player->right_rotate = true;
    if (keycode == ESC)
    {
        cleanup(game);
        exit(0);
    }
    return (0);
}

int key_release(int keycode, t_game *game)
{
    t_player *player = &game->player;

    if (keycode == W)
        player->key_up = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == D)
        player->key_right = false;
    if (keycode == LEFT)
        player->left_rotate = false;
    if (keycode == RIGHT)
        player->right_rotate = false;
    return (0);
}

void    move_player(t_player *player)
{
    int speed = 3;

    if (player->key_up)
        player->pos_x -= speed;
    if (player->key_down)
        player->pos_x += speed;
    if (player->key_left)
        player->pos_y -= speed;
    if (player->key_right)
        player->pos_y += speed;
}