/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:48:23 by czhu              #+#    #+#             */
/*   Updated: 2025/05/04 15:04:14 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* cal distance using delta x, delta y */
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

/* fix fish-eye effect */
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);

	if (fix_dist < 0.1f)
		fix_dist = 0.1f;
	return (fix_dist);
}

/* detect whether the ray touches the wall */
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map.grid[y][x] == '1')
		return (true);
	return (false);
}

/* put pixel into the buffer, then display */
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/* helper function for draw_loop */
void	clear_image(t_game *game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}


void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->pos_x;
	float ray_y = player->pos_y;
	float prev_x, prev_y;
	float step_x = cos_angle;
	float step_y = sin_angle;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		prev_x = ray_x;
		prev_y = ray_y;
		ray_x += step_x;
		ray_y += step_y;
	}
	if(!DEBUG)
	{
		t_wall_side wall_side = get_wall_side(ray_x, ray_y, step_x, step_y);
		float dist = fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, game);
		float height = (BLOCK / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		t_img *wall_texture = get_wall_texture(game, wall_side);
		float wallX;
		if (wall_side == WALL_EAST || wall_side == WALL_WEST)
			wallX = ray_y - floor(ray_y / BLOCK) * BLOCK;
		else
			wallX = ray_x - floor(ray_x / BLOCK) * BLOCK;
		int texX = (int)(wallX * wall_texture->width / BLOCK);
		if ((wall_side == WALL_EAST || wall_side == WALL_WEST) && step_x > 0)
			texX = wall_texture->width - texX - 1;
		if ((wall_side == WALL_NORTH || wall_side == WALL_SOUTH) && step_y < 0)
			texX = wall_texture->width - texX - 1;
		float step = (float)wall_texture->height / height;
		float texPos;
		texX = texX % wall_texture->width;
		if (texX < 0)
			texX += wall_texture->width;
		if (start_y < 0)
		{
			texPos = (0 - start_y) * step;
			start_y = 0;
		}
		else
		{
			texPos = 0;
		}
		if (end > HEIGHT)
			end = HEIGHT;
		for (int y = 0; y < start_y; y++) {
			put_pixel(i, y, game->textures.ceiling_color, game);
		}
		for (int y = start_y; y < end; y++) {
			int texY = (int)texPos % wall_texture->height;
			if (texY < 0) texY += wall_texture->height;
			texPos += step;
			int color = get_texture_pixel(wall_texture, texX, texY);
			float shade = 1.0f - (dist / (WIDTH / 2));
			if (shade < 0.2f) shade = 0.2f;
			if (shade > 1.0f) shade = 1.0f;
			int r = ((color >> 16) & 0xFF) * shade;
			int g = ((color >> 8) & 0xFF) * shade;
			int b = (color & 0xFF) * shade;
			int shaded_color = (r << 16) | (g << 8) | b;
			put_pixel(i, y, shaded_color, game);
		}
		for (int y = end; y < HEIGHT; y++)
		{
			put_pixel(i, y, game->textures.floor_color, game);
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_x;
	float		ray_y;
	float		cos_angle;
	float		sin_angle;

	player = &game->player;
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player(player, game);
	clear_image(game);
	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle + PI / 6;
	int i = 0;
	while(i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x -= fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

t_wall_side	get_wall_side(float ray_x, float ray_y, float dx, float dy)
{
	int map_x = ray_x / BLOCK;
	int map_y = ray_y / BLOCK;

	float prev_x = ray_x - dx;
	float prev_y = ray_y - dy;
	int prev_map_x = prev_x / BLOCK;
	int prev_map_y = prev_y / BLOCK;

	if (prev_map_x < map_x)
		return (WALL_WEST);
	else if (prev_map_x > map_x)
		return (WALL_EAST);
	if (prev_map_y < map_y)
		return (WALL_NORTH);
	else if (prev_map_y > map_y)
		return (WALL_SOUTH);
	return WALL_NORTH;
}