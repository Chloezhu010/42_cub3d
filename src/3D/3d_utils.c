/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:07:35 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 18:08:44 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* cal distance using delta x, delta y */
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_dist_data *data, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = data->end_x - data->start_x;
	delta_y = data->end_y - data->start_y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
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
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
