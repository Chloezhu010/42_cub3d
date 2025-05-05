/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:01:07 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 18:01:36 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

void	draw_ceiling(int i, int start_y, t_game *game)
{
	int	y;

	y = 0;
	while (y < start_y)
	{
		put_pixel(i, y, game->textures.ceiling_color, game);
		y++;
	}
}

void	draw_floor(int i, int end, t_game *game)
{
	int	y;

	y = end;
	while (y < HEIGHT)
	{
		put_pixel(i, y, game->textures.floor_color, game);
		y++;
	}
}

void	cast_ray(t_player *player, float angle, float *ray_pos)
{
	ray_pos[0] = player->pos_x;
	ray_pos[1] = player->pos_y;
	ray_pos[2] = cos(angle);
	ray_pos[3] = sin(angle);
}

void	update_ray(float *ray_pos)
{
	ray_pos[0] += ray_pos[2];
	ray_pos[1] += ray_pos[3];
}

int	calc_tex_x(t_wall_side side, float *ray_pos, t_img *tex)
{
	float	wall_x;
	int		tex_x;

	if (side == WALL_EAST || side == WALL_WEST)
		wall_x = ray_pos[1] - floor(ray_pos[1] / BLOCK) * BLOCK;
	else
		wall_x = ray_pos[0] - floor(ray_pos[0] / BLOCK) * BLOCK;
	tex_x = (int)(wall_x * tex->width / BLOCK);
	if ((side == WALL_EAST || side == WALL_WEST) && ray_pos[2] > 0)
		tex_x = tex->width - tex_x - 1;
	if ((side == WALL_NORTH || side == WALL_SOUTH) && ray_pos[3] < 0)
		tex_x = tex->width - tex_x - 1;
	tex_x = tex_x % tex->width;
	if (tex_x < 0)
		tex_x += tex->width;
	return (tex_x);
}
