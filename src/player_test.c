/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:26:22 by auzou             #+#    #+#             */
/*   Updated: 2025/05/03 18:29:38 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

// void    init_player(t_player *player)
// {
//     player->pos_x = WIDTH / 2;
//     player->pos_y = HEIGHT / 2;
//     player->angle = PI / 2; // initial angle, facing upwards

//     player->key_up = false;
//     player->key_down = false;
//     player->key_right = false;
//     player->key_left = false;

//     player->left_rotate = false;
//     player->right_rotate = false;
// }

int	key_press(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
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
int	key_release(int keycode, t_game *game)
{
	t_player	*player;

	player = &game->player;
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
void	move_player(t_player *player, t_game *game)
{
	int speed = 3;
	float angle_speed = 0.03;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);

	if (player->left_rotate)
		player->angle += angle_speed;
	if (player->right_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up && !touch(player->pos_x + (cos_angle * speed)
			, player->pos_y + (sin_angle * speed), game))
	{
		player->pos_x += cos_angle * speed;
		player->pos_y += sin_angle * speed;
	}
	if (player->key_down && !touch(player->pos_x - (cos_angle * speed)
			, player->pos_y - (sin_angle * speed), game))
	{
		player->pos_x -= cos_angle * speed;
		player->pos_y -= sin_angle * speed;
	}
	if (player->key_left && !touch(player->pos_x + (sin_angle * speed)
			, player->pos_y - (cos_angle * speed), game))
	{
		player->pos_x += sin_angle * speed;
		player->pos_y -= cos_angle * speed;
	}
	if (player->key_right && !touch(player->pos_x - (sin_angle * speed)
			, player->pos_y + (cos_angle * speed), game))
	{
		player->pos_x -= sin_angle * speed;
		player->pos_y += cos_angle * speed;
	}
}