/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:02:54 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 18:08:56 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

static int	apply_shade(int color, float shade)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
	return ((r << 16) | (g << 8) | b);
}

static void	draw_wall_slice(t_render_data *rd, t_game *game, int i)
{
	int		y;
	int		tex_y;
	int		color;
	float	shade;

	y = rd->start_y;
	while (y < rd->end)
	{
		tex_y = (int)rd->tex_pos % rd->tex->height;
		if (tex_y < 0)
			tex_y += rd->tex->height;
		rd->tex_pos += rd->step;
		color = get_texture_pixel(rd->tex, rd->tex_x, tex_y);
		shade = 1.0f - (rd->dist / (WIDTH / 2));
		if (shade < 0.2f)
			shade = 0.2f;
		if (shade > 1.0f)
			shade = 1.0f;
		put_pixel(i, y, apply_shade(color, shade), game);
		y++;
	}
}

static void	prepare_render_data(t_render_data *rd, t_game *game,
	float *ray_pos, t_player *player)
{
	t_dist_data	dist_data;

	rd->side = get_wall_side(ray_pos[0], ray_pos[1], ray_pos[2], ray_pos[3]);
	dist_data.start_x = player->pos_x;
	dist_data.start_y = player->pos_y;
	dist_data.end_x = ray_pos[0];
	dist_data.end_y = ray_pos[1];
	rd->dist = fixed_dist(&dist_data, game);
	rd->height = (BLOCK / rd->dist) * (WIDTH / 2);
	rd->start_y = (HEIGHT - rd->height) / 2;
	rd->end = rd->start_y + rd->height;
	rd->tex = get_wall_texture(game, rd->side);
	rd->tex_x = calc_tex_x(rd->side, ray_pos, rd->tex);
	rd->step = (float)rd->tex->height / rd->height;
}

static void	render_wall(t_render_data *rd, t_game *game, int i)
{
	if (rd->start_y < 0)
	{
		rd->tex_pos = (0 - rd->start_y) * rd->step;
		rd->start_y = 0;
	}
	else
		rd->tex_pos = 0;
	if (rd->end > HEIGHT)
		rd->end = HEIGHT;
	draw_ceiling(i, rd->start_y, game);
	draw_wall_slice(rd, game, i);
	draw_floor(i, rd->end, game);
}

void	draw_line(t_player *player, t_game *game, float angle, int i)
{
	float			ray_pos[4];
	t_render_data	rd;

	cast_ray(player, angle, ray_pos);
	while (!touch(ray_pos[0], ray_pos[1], game))
	{
		if (DEBUG)
			put_pixel(ray_pos[0], ray_pos[1], 0xFF0000, game);
		update_ray(ray_pos);
	}
	if (!DEBUG)
	{
		prepare_render_data(&rd, game, ray_pos, player);
		render_wall(&rd, game, i);
	}
}
